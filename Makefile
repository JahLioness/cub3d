CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

NAME = cub3d

SRC = main.c \
		parse.c \
		init.c
		

HEADER = cub.h

LIBFT = libft/libft.a

MiniLibX = minilibx-linux

MiniLibX_exec = minilibx-linux/libmlx.a

OBJ = $(SRC:.c=.o)

GREEN = \033[0;32m
BLUE = \033[0;34m
CYAN = \033[0;36m
YELLOW = \033[0;33m
PURPLE = \033[0;35m
NC = \033[0m

all: $(MiniLibX_exec) $(NAME)

$(NAME): $(OBJ) $(HEADER) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline
	@echo "$(GREEN)		*----------------------------------*\n \
			|   	[OK] $(NAME) created     |\n \
			*----------------------------------*$(NC)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C libft
	@echo "$(BLUE)		*----------------------------------*\n \
			|        [OK] LIBFT created        |\n \
			*----------------------------------*$(NC)"

$(MiniLibX):
	@git clone https://github.com/42Paris/minilibx-linux.git $@

$(MiniLibX_exec): $(MiniLibX)
	@make -s -C minilibx-linux
	@echo "$(CYAN)			*----------------------------------*\n \
				|        [OK] MiniLibX created     |\n \
				*----------------------------------*$(NC)"

clean:
	@make clean -C libft
	@echo "$(YELLOW)[OK]$(NC) libft clean completed"
	@make clean -C minilibx-linux
	rm -f $(OBJ)
	@echo "$(PURPLE)[OK]$(NC) cub3d clean completed"

fclean: clean
	@rm -rf $(MiniLibX)
	@make fclean -C libft
	@echo "$(YELLOW)[OK]$(NC) libft fclean completed"
	rm -f $(NAME)
	@echo "$(PURPLE)[OK]$(NC) cub3d fclean completed"

re: fclean all

.PHONY: all clean fclean re