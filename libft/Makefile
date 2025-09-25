NAME	=	libft.a

SRCS	=	ft_atoi.c \
					ft_bzero.c \
					ft_calloc.c \
					ft_isalnum.c \
					ft_isalpha.c \
					ft_islower.c \
					ft_isupper.c \
					ft_isascii.c \
					ft_isdigit.c \
					ft_isprint.c \
					ft_memchr.c \
					ft_memcmp.c \
					ft_memcpy.c \
					ft_memmove.c \
					ft_memset.c \
					ft_strchr.c \
					ft_strdup.c \
					ft_strlcat.c \
					ft_strlcpy.c \
					ft_strlen.c \
					ft_strncmp.c \
					ft_strnstr.c \
					ft_strrchr.c \
					ft_tolower.c \
					ft_toupper.c \
					ft_substr.c \
					ft_strtrim.c \
					ft_strjoin.c \
					ft_split.c \
					ft_itoa.c \
					ft_strmapi.c \
					ft_striteri.c \
					ft_putchar_fd.c \
					ft_putstr_fd.c \
					ft_putendl_fd.c \
					ft_putnbr_fd.c \
					ft_printf_utils.c \
					ft_printf.c \
					get_next_line.c \
					ft_array_dup.c \
					ft_array_print.c \
					ft_array_clear.c \
					ft_array_join.c \
					ft_strjoin_array.c \
					ft_arraylen.c \
					ft_lstnew.c \
					ft_lstadd_front.c \
					ft_lstadd_back.c \
					ft_lstclear.c \
					ft_lstdelone.c \
					ft_lstiter.c \
					ft_lstlast.c \
					ft_lstmap.c \
					ft_lstnew.c \
					ft_lstsize.c \
					ft_strcmp.c \

OBJS	=	$(addprefix objs/, $(SRCS:.c=.o))

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

CC	=	gcc


# Couleurs
GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m
CYAN = \033[0;36m
GRAY = \033[0;37m

RM	=	@rm -fr


all: $(NAME)
	@echo "$(GREEN)[LIBFT] [Success]$(NC) Library is ready."

$(NAME): $(OBJS)
	@if [ -f .compiling ]; then \
		printf "]\n"; \
		echo "$(GREEN)[LIBFT] [Success]$(NC) All source files compiled successfully."; \
		rm -f .compiling; \
	fi
	@echo "$(CYAN)[LIBFT] Creating $(NC)$(NAME)"
	@ar -rcs $(NAME) $(OBJS)

objs:
	@mkdir -p objs

objs/%.o: %.c | objs
	@if [ ! -f .compiling ]; then \
		printf "$(CYAN)[LIBFT] Compiling $(NC)["; \
		touch .compiling; \
	fi
	@printf "$(GRAY).$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)[LIBFT] [Cleaning]$(NC) Object files removed."
	@rm -rf ./objs
	@rm -f .compiling


fclean:	clean
	@echo "$(RED)[LIBFT] [Cleaning]$(NC) Library removed."
	$(RM) $(NAME)


re:	fclean all


.PHONY:	all re clean fclean