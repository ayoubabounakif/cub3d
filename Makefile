# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/19 04:43:58 by aabounak          #+#    #+#              #
#    Updated: 2020/11/19 11:03:58 by aabounak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror

MLX = -I /usr/local/include -L /usr/local/lib -lmlx

FRAMEWORKS = -framework OpenGl -framework Appkit

LIBNAME = libft.a

NAME = cub3D

EXEC = cub3D

SRC = cub3d.c render_3d.c \
read_file.c read_map.c \
init_textures.c \
utils.c random_utils.c \
draw_minimap.c \
get_next_line/get_next_line.c \
get_next_line/get_next_line_utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBNAME):
	make -C libft/
	cp libft/$(LIBNAME) .

$(NAME): $(LIBNAME)
	gcc $(FLAGS) $(SRC) -g3 -I /usr/local/include libft.a -L /usr/local/lib -lmlx $(FRAMEWORKS) -D BUFFER_SIZE=20 -o $(EXEC)
	# We can add the flag "-Ofast" to run the game way more smoothly

clean:
	make clean -C libft/
	rm -f *.o

fclean: clean
	make fclean -C libft/
	rm -f *.a
	rm -f $(EXEC)

re: fclean all
