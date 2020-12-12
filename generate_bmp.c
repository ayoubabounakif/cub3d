/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_bmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 19:10:26 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/12 19:54:27 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_headers(unsigned char *bmpfileheader, unsigned char *bmpinfoheader)
{
	int		filesize;

	filesize = 54 + 3 * WIN_WIDTH * WIN_HEIGHT;
	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);
	bmpinfoheader[4] = (unsigned char)(WIN_WIDTH);
	bmpinfoheader[5] = (unsigned char)(WIN_WIDTH >> 8);
	bmpinfoheader[6] = (unsigned char)(WIN_WIDTH >> 16);
	bmpinfoheader[7] = (unsigned char)(WIN_WIDTH >> 24);
	bmpinfoheader[8] = (unsigned char)(WIN_HEIGHT);
	bmpinfoheader[9] = (unsigned char)(WIN_HEIGHT >> 8);
	bmpinfoheader[10] = (unsigned char)(WIN_HEIGHT >> 16);
	bmpinfoheader[11] = (unsigned char)(WIN_HEIGHT >> 24);
}

void	write_bmp_data(int fd, char *bitmap)
{
	int		paddingSize;
	int		i;
	int		j;

	paddingSize = (4 - (WIN_WIDTH * 3) % 4) % 4;
	i = -1;
	while (++i < WIN_HEIGHT)
	{
		j = -1;
		while (++j < WIN_WIDTH)
			write(fd, g_mlx.data + (j + (WIN_HEIGHT - i) * WIN_WIDTH), 3);
		write(fd, bitmap, paddingSize);
	}
}

void	bmp_save(void)
{
	unsigned char	bmpfileheader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
	unsigned char	bmpinfoheader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
	char	bitmap[3] = {0, 0, 0};
	int		fd;

	init_headers(bmpfileheader, bmpinfoheader);
	fd = open("screenshot.bmp", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	write(fd, bmpfileheader, 14);
	write(fd, bmpinfoheader, 40);
	write_bmp_data(fd, bitmap);
	free(g_mlx.data);
}