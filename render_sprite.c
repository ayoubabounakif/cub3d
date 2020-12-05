/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 05:24:27 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/05 18:12:42 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "cub3d.h"

void	init_spt_tex(int k)
{
	if (!(g_sprite[k]->ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr,
					g_data.paths.sp, &g_sprite[k]->width, &g_sprite[k]->height)))
		ft_exit("Error\nSprite texture file not valid\n");
	g_sprite[k]->data = (int *)mlx_get_data_addr(g_sprite[k]->ptr,
					&g_sprite[k]->bpp, &g_sprite[k]->size_line, &g_sprite[k]->endian);
}

void    render_sprite(int k, int x_fs, int y_fs)
{
    int		i;
    int		j;
    int		color;

	init_spt_tex(k);
    i = 0;
    while (i++ < (int)g_sprite[k]->size)
    {
        if (x_fs + i < 0 || x_fs + i > WIN_WIDTH)
            continue;
        if (g_rays[(int)(x_fs + i)].distance <= g_sprite[k]->distance)
            continue;
        j = 0;
		while (j++ < (int)g_sprite[k]->size)
        {
            if (y_fs + j < 0 || y_fs + j > WIN_HEIGHT)
                continue;
            color = g_sprite[k]->data[(int)(g_sprite[k]->width * (j *
					g_sprite[k]->height / (int)g_sprite[k]->size) +
            		(i * g_sprite[k]->width / (int)g_sprite[k]->size))];
			if (color)
				img_update(x_fs + i, y_fs + j, color);
        }
    }
}

void		ft_sprite_traits(int i)
{
	float	x_offset;
	float	y_offset;

	x_offset = 0;
	y_offset = 0;
	g_player.rotation_angle = normalize_angle(g_player.rotation_angle);
	g_sprite[i]->angle = atan2(-g_player.y + (g_sprite[i]->y),
                            -g_player.x + (g_sprite[i]->x));
    while (g_sprite[i]->angle - g_player.rotation_angle > M_PI)
        g_sprite[i]->angle -= TWO_PI;
    while (g_sprite[i]->angle - g_player.rotation_angle < -M_PI)
        g_sprite[i]->angle += TWO_PI;
	g_sprite[i]->size = (WIN_WIDTH / g_sprite[i]->distance * 64);
    x_offset = (g_sprite[i]->angle - g_player.rotation_angle) * WIN_WIDTH
    / RAD(60) + (WIN_WIDTH / 2 - g_sprite[i]->size / 2);
    y_offset = WIN_HEIGHT / 2 - g_sprite[i]->size / 2;

	printf("----------######----------\n");
	printf("g_player.rotation_angle %f\n", g_player.rotation_angle);
	printf("g_sprite[i]->angle %f\n", g_sprite[i]->angle);
	printf("g_sprite[i]->size %f\n", g_sprite[i]->size);
	printf("g_sprite[i]->distance %f\n", g_sprite[i]->distance);
	printf("x_offset %f\n", x_offset);
	printf("y_offset %f\n", y_offset);
	printf("g_sprite_count %d\n", g_sprite_count);
	printf("--------------------------\n");
    render_sprite(i, x_offset, y_offset);
}

void		ft_sprite(void)
{
	int		i;

	init_sprite();
	i = -1;
	while (++i < g_sprite_count)
		ft_sprite_traits(i);
	free(g_sprite);
}
