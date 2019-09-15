NAME = fractol

SRCDIR = ./src/
INCDIR = ./inc/
SRC = main.c \
	setup.c \
	colors.c \
	colors_helper.c \
	fractol.c \
	fractol_helper.c \
	hooks.c \
	hooks_helper.c \
	info_menu.c

OBJ = $(SRC:.c=.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror -g

MLX = ./minilibx_macos/
MLX_LNK = -L ./minilibx_macos/ -lmlx -framework OpenGL -framework AppKit
FT = ./libft/
FT_LNK = -L ./libft -lft

all: $(NAME)

%.o:$(SRCDIR)%.c
	$(CC) $(FLAGS) -I $(INCDIR) -I $(FT) -I $(MLX) -c $< -o $@

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