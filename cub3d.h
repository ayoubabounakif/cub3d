/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 11:07:45 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/03 10:27:04 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <math.h>
# include <errno.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

# define TRUE 1
# define FALSE 0

# define RAD(x) (x * M_PI / 180)
# define DEG(x) (x * 180 / M_PI)
# define TWO_PI (M_PI * 2)

// KEYS
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define UP_ARROW 126
# define LEFT_ARROW 123
# define DOWN_ARROW 125
# define RIGHT_ARROW 124
# define ESC 53

// MAP
# define TILE_SIZE 64
# define ROWS g_sizeofmap
# define COLS g_biglen

// WINDOW
# define WIN_WIDTH COLS * TILE_SIZE		// x
# define WIN_HEIGHT ROWS * TILE_SIZE	// y

# define R_WIDTH g_data.win_width
# define R_HEIGHT g_data.win_height

// TEXTURE
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

// PLAYER
# define SIZE 6
# define MOVEMENT_SPEED 6
# define ROTATION_SPEED 0.05

// RAYS
# define FOV_ANGLE RAD(60)
# define NUM_RAYS WIN_WIDTH

/*
    Here is my main struct containing every variables needed by the MLX.
        - mlx_ptr stores the return value of mlx_init
    	- win stores the return value of mlx_new_window
    	- img will store everything we need for the image part, the struct is described above.
*/

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

typedef struct	s_vars   // This struct contains random variables.
{
    int     	i;
    int     	j;
    int     	x;
    int     	y;
    int     	rows;
    int     	cols;
}               t_vars;

// Player struct
typedef struct	s_player
{
    float		x;
	float		y;
	float		renderer_x;
	float		renderer_y;
	float		rotation_angle;
	float		rotation_speed;
    float       movement_speed;
	int			move_up;
	int			move_down;
	int			move_left;
	int			move_right;
}				t_player;

// Rays struct

typedef	struct s_vray
{
	float		xToCheck;
	float		yToCheck;
}				t_vray;

typedef struct	s_ray
{
	int			isRayFacingUp;
	int			isRayFacingDown;
	int			isRayFacingLeft;
	int			isRayFacingRight;
	
	float		xintercept;
	float		yintercept;

	float		xstep;
	float		ystep;

	// HORIZONTAL
	int			foundHorzWallHit;
	float		horzWallHitX;
	float		horzWallHitY;
	int			horzWallContent;
	
	float		nextHorzTouchX;
	float		nextHorzTouchY;

	// VERTICAL
	int			foundVertWallHit;
	float		vertWallHitX;
	float		vertWallHitY;
	int			vertWallContent;
	
	float		nextVertTouchX;
	float		nextVertTouchY;
	
	float		xToCheck;
	float		yToCheck;
	
	// OTHER VARS
	float		horzHitDistance;
	float		vertHitDistance;
	
}				t_ray;

typedef struct	s_rays
{
	int			columnId;
	float		rayAngle;
	float		wallHitX;
	float		wallHitY;
	float		distance;
	int			isRayFacingUp;
	int			isRayFacingDown;
	int			isRayFacingLeft;
	int			isRayFacingRight;
	int			wasHitVertical;
	int			wallHitContent;
}				t_rays;

// PATHS STRUCTURE

typedef	struct	s_paths
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*sp;
}				t_paths;

typedef	struct	s_data
{
	int			win_width;
	int			win_height;
	int			floor_color;
	int			ceiling_color;
	t_paths		paths;
}				t_data;

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_tex
{
	void		*ptr;
	int			img_width;
	int			img_height;
	int			bpp;
	int			size_line;
	int			endian;

	int			texOffSetX;
	int			texOffSetY;
	int			distanceFromTop;
	int			texelColor;
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
	float		angle;
	float		size;
}				t_sprite;

// GLOBAL STRUCTURES
t_mlx			g_mlx;
t_vars			g_vars;
t_player		g_player;
t_ray			g_ray;
t_vray			g_vray;
t_data			g_data;
t_rays			*g_rays;
t_list			*g_file;
t_tex			g_tex;
t_sprite		**g_sprite;
t_color			g_floor_rgb;
t_color			g_ceiling_rgb;

// GLOBAL VARIABLES
char			**g_mapread;
int				g_sizeofmap;
int				g_biglen;

// GLOBAL VARIABLE FOR FLOOR AND CEILING
int				*hex_floor;
int				*hex_ceiling;

// TEXTURE GLOBAL VARIABLES
int				*g_textnorth;
int				*g_textwest;
int				*g_texteast;
int				*g_textsouth;
void			*tempimage;
int				g_sprite_count;

// // EVENTS | HOOKS | LOOPS (UTILS.C)
int			key_pressed(int keycode);
int			key_released(int keycode);
int			loop_key(void);
int			deal_key(void);

// RANDOM UTILS
void		img_update(int x, int y, int color);
int			abs(int n);
float		distanceBetweenPoints(float x1, float y1, float x2, float y2);
float		normalize_angle(float angle);
int			wall_collision(float x, float y);
void		draw_square(int y, int x, int size, int color);
void		init_player(void);
void		set_rotation_angle(char player_pos);

// RAY CASTING FUNCTIONS
void		castAllRays(void);

// FILE FUNCTIONS
void		ft_exit(char *msg);
void		read_file();
void		check(char *buffer);
void		resolution(char *buffer);
void		ft_floor(char *buffer);
void		ft_ceiling(char *buffer);
void		check_map(void);

// MINIMAP FUNCTIONS
void		draw_map(void);
void		drawsquare(int x, int y, int color);
void		drawemptysquare(int x, int y, int color);
void		put_character(void);
void		draw_line(int X0, int Y0, int X1, int Y1, int color);

// 3D FUNCTIONS
void		render3DProjectionPlane(int i);
int			rgb_to_int(int r, int g, int b);
void		draw_wall(int i, int wallTopPixel, int wallBottomPixel, int wallStripHeight);
void		draw_ceiling(int i, int wallTopPixel);
void		draw_floor(int i, int wallBottomPixel);

// SP FUNCTIONS
void		ft_sprite(void);

// INIT FUNCTIONS
void		init_tex(void);
#endif