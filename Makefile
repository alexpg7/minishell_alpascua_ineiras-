NAME = minishell
FLAGS = -Wall -Wextra -Werror
OPTION = -MMD -c -I.
# Paths
LIBFT_PATH = lib/Libft
LIBMINI_PATH = lib/libminishell

INCLUDE = Makefile $(LIBFT_PATH)/libft.h $(LIBMINI_PATH)/libminishell.h src/minishell.h

# Library files
LIBFT = $(LIBFT_PATH)/libft.a

# Source and object files
SRC = src/minishell.c \
	src/ft_init.c \
	commands/exit.c \
	commands/pwd.c \
	commands/ft_env.c \
	lib/libminishell/ft_splitmini.c \

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

# Compile the final executable
all: $(NAME)

-include $(DEP)

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

.PHONY: all, clean, fclean, re
