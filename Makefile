NAME = minishell
FLAGS = -Wall -Wextra -Werror
OPTION = -MMD -c -I.
# Paths
LIBFT_PATH = lib/Libft

INCLUDE = $(LIBFT_PATH)/libft.h src/minishell.h

# Library files
LIBFT = $(LIBFT_PATH)/libft.a

# Source and object files
SRC = src/minishell.c \
	src/ft_init.c \
	src/signals.c  \
	src/signals2.c  \
	commands/exit.c \
	commands/pwd.c \
	commands/ft_cd.c \
	commands/ft_cd2.c \
	commands/ft_cd3.c \
	commands/ft_cd_utils.c \
	commands/ft_echo.c \
	commands/ft_env.c \
	commands/ft_export.c \
	commands/ft_unset.c \
	execution/ft_heredoc.c \
	execution/ft_execute.c \
	execution/file_descriptors.c \
	execution/ft_execute_utils.c \
	execution/ft_execute_utils2.c \
	execution/ft_execmore.c \
	execution/ft_execute_first.c \
	execution/ft_execute_between.c \
	execution/ft_execute_last.c \
	execution/exit_status.c \
	execution/ft_findpath.c \
	lib/libminishell/ft_splitmini.c \
	lib/libminishell/ft_splitmini_utils.c \
	lib/libminishell/createcommand_utils.c \
	lib/libminishell/createcommand.c \
	lib/libminishell/ft_searchdollar.c \
	lib/libminishell/ft_searchdollar_utils.c \
	lib/libminishell/remove_quotes.c \
	lib/libminishell/trashlist.c \

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

# Compile the final executable
all: $(NAME)

# Rebuild Libft if any object file changes
$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

# Build the main program
#$(NAME): $(OBJ) $(LIBFT) $(PRINTF)
#	cc $(FLAGS) $(OBJ) $(LIBFT) $(PRINTF) $(MINILIBX) -o $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(FLAGS) $(LIBFT) -lreadline -o $(NAME)

# Compile object files and generate .d files for dependencies
%.o: %.c $(INCLUDE)
	cc $(FLAGS) $(OPTION) $< -o $@

# Include the generated dependency files
-include $(DEP)

# Clean object and dependency files
clean:
	/bin/rm -f $(OBJ) $(DEP)
	$(MAKE) -C $(LIBFT_PATH) clean

# Full clean
fclean: clean
	/bin/rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean

# Rebuild everything
re: fclean all

val: all readline.supp
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell

.PHONY: all, clean, fclean, re
