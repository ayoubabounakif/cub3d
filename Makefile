# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/19 04:43:58 by aabounak          #+#    #+#              #
#    Updated: 2020/12/16 13:17:46 by aabounak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror

MLX = -I /usr/local/include -L /usr/local/lib -lmlx

FRAMEWORKS = -framework OpenGl -framework Appkit

LIBNAME = libft.a

NAME = cub3D

EXEC = cub3D

SRC = cub3d.c render_3d.c cast_vert.c cast_horz.c \
render_sprite.c sprite_utils.c \
args_error.c read_file.c file_pcheck.c file_helpers.c \
read_map.c map_spacers.c free_map.c \
init.c \
set_rangle.c wall_collision.c\
events.c utils.c \
generate_bmp.c \
get_next_line/get_next_line.c \
get_next_line/get_next_line_utils.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBNAME):
	make -C libft/
	cp libft/$(LIBNAME) ./

$(NAME): $(LIBNAME)
	gcc -g3 -fsanitize=address $(FLAGS) $(SRC) libft.a $(MLX) $(FRAMEWORKS) -D BUFFER_SIZE=20 -o $(EXEC)
	# We can add the flag "-Ofast" to run the game way more smoothly
	# export MallocStackLogging=1 for debugging leaks before using cmd leaks

clean:
	make clean -C libft/
	rm -f *.o

fclean: clean
	make fclean -C libft/
	rm -f *.a
	rm -f $(EXEC)

re: fclean all
