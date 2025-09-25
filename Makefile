NAME		=	ft_nm

SRCDIR		=	src
OBJDIR		=	objs
INCDIR		=	includes
LIBFTDIR	=	libft

SRCS		=	main.c \
				ft_nm.c \
				elf_detect.c \
				elf64.c \
				elf32.c \
				handle_arg.c \
				utils.c \

OBJS		=	$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

LIBFT		=	$(LIBFTDIR)/libft.a

CFLAGS		=	-Wall -Wextra -Werror #-fsanitize=address -g3
CC			=	gcc

# Couleurs
GREEN 		= \033[0;32m
RED 		= \033[0;31m
NC 			= \033[0m
CYAN 		= \033[0;36m
GRAY 		= \033[0;37m
YELLOW		= \033[0;33m

RM			=	@rm -fr

all: $(NAME)
	@echo "$(GREEN)[FT_NM] [Success]$(NC) $(NAME) is ready."

$(NAME): $(LIBFT) $(OBJS)
	@if [ -f .compiling ]; then \
		printf "]\n"; \
		echo "$(GREEN)[FT_NM] [Success]$(NC) All source files compiled successfully."; \
		rm -f .compiling; \
	fi
	@echo "$(CYAN)[FT_NM] Linking $(NC)$(NAME)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@echo "$(YELLOW)[FT_NM] Building libft$(NC)"
	@$(MAKE) --no-print-directory -C $(LIBFTDIR)
	@echo "$(YELLOW)[FT_NM] Building nm$(NC)"


$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@if [ ! -f .compiling ]; then \
		printf "$(CYAN)[FT_NM] Compiling $(NC)["; \
		touch .compiling; \
	fi
	@printf "$(GRAY).$(NC)"
	@$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBFTDIR) -c $< -o $@

clean:
	@echo "$(RED)[FT_NM] [Cleaning]$(NC) Object files removed."
	@rm -rf $(OBJDIR)
	@rm -f .compiling
	@$(MAKE) --no-print-directory -C $(LIBFTDIR) clean

fclean: clean
	@echo "$(RED)[FT_NM] [Cleaning]$(NC) $(NAME) removed."
	$(RM) $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re