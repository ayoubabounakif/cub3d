/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 11:07:45 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/15 17:07:35 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// Libraries
# include "mlx.h"
# include <math.h>
# include <errno.h>
# include <time.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

// Duhh
# define TRUE 1
# define FALSE 0

// Conversions
# define RAD(x) (x * M_PI / 180)
# define DEG(x) (x * 180 / M_PI)
# define TWO_PI (M_PI * 2)
# define H_PI (M_PI / 2)
# define PI_H (M_PI * 1.5)

// Keycodes
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define UP_ARROW 126
# define LEFT_ARROW 123
# define DOWN_ARROW 125
# define RIGHT_ARROW 124
# define ESC 53

// Map
# define TILE_SIZE 64
# define ROWS g_sizeofmap
# define COLS g_biglen

// Window Dimensions
# define WIN_WIDTH g_data.win_width
# define WIN_HEIGHT g_data.win_height

// Texture Dimensions
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

// Player
# define SIZE 6
# define MOVEMENT_SPEED 6
# define ROTATION_SPEED 0.04

// Field of View
# define FOV_ANGLE RAD(60)

// MLX
typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			bpp;
	int			size_line;
	int			endian;
	int			*data;
	void		*img_ptr;
}				t_mlx;

// Player
typedef struct	s_player
{
	float		x;
	float		y;
	float		rangle;
}				t_player;

// Keys
typedef	struct	s_key
{
	int			move_straight;
	int			move_back;
	int			left_dir;
	int			right_dir;
}				t_key;

// Ray
typedef struct	s_ray
{
	int			isray_up;
	int			isray_down;
	int			isray_left;
	int			isray_right;
	float		offs_x;
	float		offs_y;
	float		xstep;
	float		ystep;
	int			fhorz_hit;
	float		horz_hit_x;
	float		horz_hit_y;
	float		next_htouch_x;
	float		next_htouch_y;
	int			fvert_hit;
	float		vert_hit_x;
	float		vert_hit_y;
	float		next_vtouch_x;
	float		next_vtouch_y;
	float		x_check;
	float		y_check;
	float		horz_hit_dist;
	float		vert_hit_dist;
}				t_ray;

// Rays
typedef struct	s_rays
{
	float		ray_angle;
	float		wall_hit_x;
	float		wall_hit_y;
	float		distance;
	int			isray_up;
	int			isray_down;
	int			isray_left;
	int			isray_right;
	int			was_hit_vert;
}				t_rays;

// Paths
typedef	struct	s_paths
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*sp;
}				t_paths;

// Data
typedef	struct	s_data
{
	int			win_width;
	int			win_height;
	int			floor_color;
	int			ceiling_color;
	t_paths		paths;
}				t_data;

// RGB
typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

// Textures
typedef struct	s_tex
{
	void		*ptr;
	int			img_width;
	int			img_height;
	int			bpp;
	int			size_line;
	int			endian;
	int			offset_x;
	int			offset_y;
	int			dist_ftop;
	int			color;
}				t_tex;

typedef struct	s_sprite
{
	void		*ptr;
	int			*data;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
	float		x;
	float		y;
	float		distance;
}				t_sprite;

// Defining the following t_structures as global_structures
t_mlx		g_mlx;
t_player	g_player;
t_key		g_key;
t_ray		g_ray;
t_data		g_data;
t_rays		*g_rays;
t_list		*g_file;
t_tex		g_tex;
t_sprite	**g_sprite;
t_color		g_floor_rgb;
t_color		g_ceiling_rgb;

// Map related global variables
char		**g_map;
int			g_sizeofmap;
int			g_biglen;

// Textures related global variables
int			*g_texnorth;
int			*g_texwest;
int			*g_texeast;
int			*g_texsouth;
int			g_sprite_count;

// Events || Hooks || Loops (events.c)
int			key_pressed(int keycode);
int			key_released(int keycode);
int			loop_key(void);
int			deal_key(void);

// Set rotation angle (set_rangle.c)
void		set_rangle(char player_pos);

// Wall collision (wall_collision.c)
int			wall_collision(float x, float y);

// Utils (utils.c)
void		img_update(int x, int y, int color);
int			abs(int n);
float		distance_bpts(float x1, float y1, float x2, float y2);
float		normalize_angle(float angle);
int			rgb_to_int(int r, int g, int b);

// Raycasting functions (cub3d.c || cast_horz.c || cast_vert.c)
void		cast_rays(void);
void		cast_horz(float ray_angle);
void		cast_vert(float ray_angle);

// Args treatment (args_error.c)
int			arg_test(int argc, char **argv);

// File reading handling (read_file.c)
void		ft_exit(char *msg);
void		read_file(int ac, char **av);
void		check(char *buffer);
void		resolution(char *buffer);
void		ft_floor(char *buffer);
void		ft_ceiling(char *buffer);

// Map reading handling (read_map.c || map_spacers.c)
void		check_map(void);
char		get_fchar(char *buffer);
char		*spacer(char *buffer, int biglen);
char		*space_filler(int biglen);
void		free_map(void);

// 2D drawing (bin/draw_minimap.c)
// void		draw_map(void);
// void		drawsquare(int x, int y, int color);
// void		drawemptysquare(int x, int y, int color);
// void		put_character(void);
// void		draw_line(int X0, int Y0, int X1, int Y1, int color);
// void		draw_square(int y, int x, int size, int color);

// 3D Rendering (render_3d.c)
void		render_3d(void);
void		draw_wall(int i, int wall_striph);
void		draw_ceiling(int i);
void		draw_floor(int i);

// Sprite rendering (render_sprite.c || sprite_utils.c)
void		init_sprite(void);
void		ft_sprite_sort(void);
void		ft_sprite(void);

// Initialization (init.c)
void		init_mlx(void);
void		init_player(void);
void		init_tex(void);

// Screenshot | Bitmap (generate_bmp.c)
void		bmp_save(void);
#endif
