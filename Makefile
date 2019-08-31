NAME = fractol

SRC = main.c

OBJ = $(SRC:.c=.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror -g

MLX = ./minilibx_macos/
MLX_LNK = -L ./minilibx_macos -l mlx -framework OpenGL -framework AppKit
FLAGS2 = -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit
FLAGS3 = /usr/local/lib/libmlx.a /usr/local/include/mlx.h -lXext -lX11 -lm
FT = ./libft/
FT_LNK = -L ./libft -lft

all: $(NAME)

%.o: %.c
	#$(CC) $(FLAGS) -I $(MLX) -I $(FT) -c $< -o $@
	$(CC) -I $(MLX) -I $(FT) -c $< -o $@

$(NAME): $(OBJ)
	make -C $(FT)
	$(CC) $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)

clean:
	rm -f $(OBJ)
	make -C $(FT) clean

fclean: clean
	rm -f $(NAME)
	make -C $(FT) fclean

re: fclean all