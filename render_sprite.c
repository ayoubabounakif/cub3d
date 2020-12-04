/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 05:24:27 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/04 04:44:23 by aabounak         ###   ########.fr       */
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
    i = -1;
    while (++i < g_sprite[k]->size)
    {
        if (x_fs + i < 0 || x_fs + i > WIN_WIDTH)
            continue;
        if (g_rays[x_fs + i].distance < g_sprite[k]->distance)
            continue;
        j = -1;
        while (++j < g_sprite[k]->size)
        {
            if (y_fs + j < 0 || y_fs + j > WIN_HEIGHT)
                continue;
            color = g_sprite[k]->data[g_sprite[k]->width * (j * g_sprite[k]->height / g_sprite[k]->size) +
            (i * g_sprite[k]->width / g_sprite[k]->size)];
			if (color)
				img_update(x_fs + i, y_fs + j, color);
        }
    }
}

void		ft_sprite_traits(int i, float x_offset, float y_offset)
{
	g_player.rotation_angle = normalize_angle(g_player.rotation_angle);
	g_sprite[i]->angle = atan2(g_sprite[i]->y - g_player.y,
						g_sprite[i]->x - g_player.x);
    while (g_sprite[i]->angle - g_player.rotation_angle >= M_PI)
        g_sprite[i]->angle -= TWO_PI;
    while (g_sprite[i]->angle - g_player.rotation_angle <= -M_PI)
        g_sprite[i]->angle += TWO_PI;
    g_sprite[i]->size = (WIN_WIDTH / g_sprite[i]->distance * TILE_SIZE);
    x_offset = (g_sprite[i]->angle - g_player.rotation_angle) * WIN_WIDTH
    / FOV_ANGLE + (WIN_WIDTH / 2 - g_sprite[i]->size / 2);
    y_offset = WIN_HEIGHT / 2 - g_sprite[i]->size / 2;
    render_sprite(i, x_offset, y_offset);	
}

void		ft_sprite(void)
{
	int		i;
	float	x_offset;
	float	y_offset;

	init_sprite();
	i = 0;
	x_offset = 0;
	y_offset = 0;
	i = -1;
	while (++i < g_sprite_count)
		ft_sprite_traits(i, x_offset, y_offset);
	free(g_sprite);
}
