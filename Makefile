C_FILES = cub3D.c \
error.c \
ft_utils.c \
parser_map.c \
get_next_line_utils.c \
get_next_line.c \
verif_closed.c \
init.c \
raycast.c \
keys.c \
move.c

SRC_DIR = ./src/
MLX_DIR = ./minilibx-linux
MLX_REPO = https://github.com/42Paris/minilibx-linux.git
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
SRC = $(addprefix $(SRC_DIR), $(C_FILES))
OFILES = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = ./cub3D

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(MLX):
	@echo "\033[1;33m\nTéléchargement de la MiniLibX...\n"
	@git clone $(MLX_REPO) $(MLX_DIR)
	@echo "\033[1;32mMiniLibX téléchargée.\n"
	@echo "\033[1;33m\nCompilation de la MiniLibX...\n"
	@make -C $(MLX_DIR)
	@echo "\033[1;32mMiniLibX compilée.\n"

$(NAME): $(MLX) $(OFILES)
	@echo "\033[1;33m\nCOMPILING CUB3D...\n"
	@$(CC) $(CFLAGS) $(OFILES) $(MLX_FLAGS) -o $(NAME)
	@echo $(addsuffix "\n", $^)
	@echo "\033[1;32m./cub3D CREATED\n"
clean:
	@echo "\033[1;31mCLEANING OBJECT FILES...\n"
	@rm -f $(OFILES)
	@make -C $(MLX_DIR) clean
	@echo "\033[1;32mDONE\n"

fclean: clean
	@echo "\033[1;31mDELETING CUB3D EXECUTABLE AND MiniLibX...\n"
	@rm -f $(NAME)
	@rm -rf $(MLX_DIR)
	@echo "\033[1;32mDONE\n"
	@echo "\033[0m"

re: fclean all

.PHONY: all clean fclean re
