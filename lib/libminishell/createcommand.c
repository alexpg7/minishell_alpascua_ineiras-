#include "../../src/minishell.h"

int	ft_commandlen(char **comm)
{
	int	i;

	i = 0;
	while (comm[i] && comm[i][0] != '|')
	{
		i++;
	}
	return (i);
}

void	ft_countredirect(char **comm, int *n_in, int *n_out)
{
	int	i;

	i = 0;
	*n_in = 0;
	*n_out = 0;
	while (comm[i] && comm[i][0] != '|')
	{
		if (ft_strcmp(comm[i], "<") == 0 || ft_strcmp(comm[i], "<<") == 0)
			*n_in = 1;
		else if (ft_strcmp(comm[i], ">") == 0 || ft_strcmp(comm[i], ">>") == 0)
			*n_out = 1;
		i++;
	}
}

void	ft_copycommand(t_command *command, char **comm, int len)
{
	int	i;
	int	flagin;
	int	flagout;

	i = 0;
	flagin = 0;
	flagout = 0;
	command->hd = 0;
	command->ap = 0;
	command->infile = NULL;
	command->outfile = NULL;
	while (i < len + 1)
	{
		if ((ft_strcmp(comm[i], "<") == 0 || ft_strcmp(comm[i], "<<") == 0) && flagin == 0)
		{
			flagin = 1;
			command->infile = comm[i + 1];
			if (ft_strcmp(comm[i], "<<") == 0)
				command->hd = 1;
			comm = comm + 2;
		}
		else if ((ft_strcmp(comm[i], ">") == 0 || ft_strcmp(comm[i], ">>") == 0) && flagout == 0)
		{
			flagout = 1;
			command->outfile = comm[i + 1];
			if (ft_strcmp(comm[i], ">>") == 0)
				command->ap = 1;
			comm = comm + 2;
			len -= 1;
		}
		else
		{
			command->comm[i] = comm[i];
			i++;
		}
	}
	command->comm[i] = NULL;
}

t_command	*ft_createcomm(char **comm, t_vars *vars)
{
	t_command	*command;
	int			i;
	int			n_in;
	int			n_out;
	int			len;

	command = (t_command *)malloc(sizeof(t_command) * (vars->np + 2));//there's 2 commands per pipe + NULL at the end
	ft_printf("LEN: %i\n", vars->np + 2);
	i = 0;
	while (i <= vars->np)
	{
		ft_countredirect(comm, &n_in, &n_out);
		len = ft_commandlen(comm) - 2 * n_in - 2 * n_out; //- 2 for each extra argument (<) (infile) + 1 for the NULL
		command[i].comm = (char **)malloc(sizeof(char *) * (len + 1)); // + 1 for the null
		ft_copycommand(&command[i], comm, len);
		comm = comm + len + 2 * n_in + 2 * n_out + 1; //step to the next command
		i++;
	}
	command[i].comm = NULL;
	return (command);
}
