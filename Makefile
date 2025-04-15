CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRCS =	srcs/minishell.c srcs/utils/utils.c srcs/parsing/tokenization.c srcs/parsing/env-to-list.c \
		srcs/parsing/handle_words.c srcs/parsing/build_ast.c srcs/parsing/build_args_node.c \
		srcs/utils/free.c srcs/utils/add_node.c srcs/parsing/expansions.c \
		srcs/builtins/cd.c srcs/builtins/echo.c srcs/builtins/env.c \
		srcs/builtins/exit.c srcs/builtins/export.c srcs/builtins/pwd.c \
		srcs/builtins/unset.c srcs/execution/begin_execution.c \

NAME =	minishell

HEADERS = -I ./libft

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

LIBS = -lreadline

GREEN = \033[32m
ORANGE = \033[38;5;214m
RESET = \033[0m

all: $(NAME)

db:
	@echo $(HEADERS)

$(LIBFT):
	@echo "$(GREEN)----------------------------------------$(RESET)"
	@echo "$(ORANGE)Compiling libft...$(RESET)"
	@echo "$(GREEN)----------------------------------------$(RESET)"
	make --no-print-directory -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(GREEN)----------------------------------------$(RESET)"
	@echo "$(ORANGE)Compiling executable...$(RESET)"
	@echo "$(GREEN)----------------------------------------$(RESET)"
	$(CC) $(CFLAGS) $(HEADERS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "$(GREEN)----------------------------------------$(RESET)"
	@echo "$(ORANGE)COMPILATION COMPLETE!$(RESET)"
	@echo "$(GREEN)----------------------------------------$(RESET)"

clean:
	@echo "$(GREEN)----------------------------------------$(RESET)"
	@echo "$(ORANGE)Cleaning object files...$(RESET)"
	@echo "$(GREEN)----------------------------------------$(RESET)"
	rm -f $(OBJS)
	make clean --no-print-directory -C $(LIBFT_DIR)

fclean: clean
	@echo "$(GREEN)----------------------------------------$(RESET)"
	@echo "$(ORANGE)Removing executables and libraries...$(RESET)"
	@echo "$(GREEN)----------------------------------------$(RESET)"
	rm -f $(NAME) $(LIBFT)

re:	fclean all

%.o: %.c minishell.h
		$(CC) $(CFLAGS) -c $< -o $@ -g $(HEADERS)

debug: CFLAGS += -fsanitize=address -fsanitize=leak -fsanitize=undefined
debug: $(NAME)
	@echo "$(GREEN)----------------------------------------$(RESET)"
	@echo "$(ORANGE)Debug with sanitizers...$(RESET)"
	@echo "$(GREEN)----------------------------------------$(RESET)"
