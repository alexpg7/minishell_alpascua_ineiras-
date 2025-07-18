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

static void	ft_setin(char **file, char **comm, int *flag, int *num)
{
	*flag= 1;
	*file = *(comm + 1);
	if (ft_strcmp(*comm, "<<") == 0 || ft_strcmp(*comm, ">>") == 0)
		*num = 1;
}

void	ft_copycommand(t_command *command, char **comm)
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
	while (comm[i] && comm[i][0] != '|')
	{
		if ((ft_strcmp(comm[i], "<") == 0 || ft_strcmp(comm[i], "<<") == 0) && flagin == 0)
		{
			ft_setin(&command->infile, &comm[i], &flagin, &command->hd);
			comm = comm + 2;
		}
		else if ((ft_strcmp(comm[i], ">") == 0 || ft_strcmp(comm[i], ">>") == 0) && flagout == 0)
		{
			ft_setin(&command->outfile, &comm[i], &flagout, &command->ap);
			comm = comm + 2;
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
	i = 0;
	while (i <= vars->np)
	{
		ft_countredirect(comm, &n_in, &n_out);
		len = ft_commandlen(comm) - 2 * n_in - 2 * n_out; //- 2 for each extra argument (<) (infile) + 1 for the NULL
		command[i].comm = (char **)malloc(sizeof(char *) * (len + 1)); // + 1 for the null
		ft_copycommand(&command[i], comm);
		comm = comm + len + 2 * n_in + 2 * n_out + 1; //step to the next command
		i++;
	}
	command[i].comm = NULL;
	return (command);
}
