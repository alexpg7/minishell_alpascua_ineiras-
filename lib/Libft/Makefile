NAME = libft.a
FLAG = -Wall -Wextra -Werror
OPTION = -MMD -c -I.
INCLUDE = Makefile libft.h

# Colors
BRED = \033[1;31m
BYEL = \033[1;33m
BGREEN = \033[1;32m
RED = \033[0;31m
YEL = \033[0;33m
GREEN = \033[0;32m
NC = \033[0m

SRC = get_next_line.c \
	ft_isdigit.c \
	ft_isalpha.c \
	ft_isalnum.c \
	ft_isalnum2.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_isspace.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_strcmp.c \
	ft_memchr.c \
	ft_memmove.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_atof.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strjoin3.c \
	ft_freestrarr.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstmap_bonus.c \
	ft_printf.c \
	ft_printtype.c \

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "📚 ${BGREEN}Compiled ${BYEL}$(NAME)${NC}"

-include $(DEP)

%.o: %.c $(INCLUDE)
	@cc $(FLAG) $(OPTION) $< -o $@

clean:
	@rm -f $(OBJ) $(DEP)
	@echo "🗑️  $(BRED)Removed $(YEL)$(OBJ)${NC}"

fclean: clean
	@rm -f $(NAME)
	@echo "🗑️  $(BRED)Removed $(BYEL)$(NAME)${NC}"

re: fclean all

#.PHONY: all, clean, fclean, re
