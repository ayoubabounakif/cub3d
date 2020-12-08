/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_bmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 19:10:26 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/08 10:28:20 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const int		BYTES_PER_PIXEL = 3;	// R, G, B
const int		FILE_HEADER_SIZE = 14;
const int		INFO_HEADER_SIZE = 40;

void			generateBitmapImage(unsigned char* image, int height, int width, char* imageFileName);
unsigned char*	createBitmapFileHeader(int height, int stride);
unsigned char*	createBitmapInfoHeader(int height, int width);

// int		main(void)
// {
//     int height = 1000;
//     int width = 1500;
//     unsigned char image[height][width][BYTES_PER_PIXEL];
//     char* imageFileName = (char*) "bitmapImage.bmp";

//     int i, j;
//     for (i = 0; i < height; i++) {
//         for (j = 0; j < width; j++) {
//             image[i][j][2] = (unsigned char)(i * 255 / height);					// RED
//             image[i][j][1] = (unsigned char)(j * 255 / width);					// GREEN
// 			image[i][j][0] = (unsigned char)((i + j) * 255 / (height + width));	// BLUE
//         }
//     }
//     generateBitmapImage((unsigned char*)image, height, width, imageFileName);
//     printf("Image generated!!");
// }


void	generateBitmapImage(unsigned char* image, int height, int width, char* imageFileName)
{
    int widthInBytes = width * BYTES_PER_PIXEL;

    unsigned char padding[3] = {0, 0, 0};
    int paddingSize = (4 - (widthInBytes) % 4) % 4;

    int stride = (widthInBytes) + paddingSize;

    void* imageFile = fopen(imageFileName, "wb");

    unsigned char*	fileHeader = createBitmapFileHeader(height, stride);
    fwrite(fileHeader, 1, FILE_HEADER_SIZE, imageFile);

    unsigned char*	infoHeader = createBitmapInfoHeader(height, width);
    fwrite(infoHeader, 1, INFO_HEADER_SIZE, imageFile);

    int	i;
    for (i = 0; i < height; i++) {
        fwrite(image + (i * widthInBytes), BYTES_PER_PIXEL, width, imageFile);
        fwrite(padding, 1, paddingSize, imageFile);
    }
    fclose(imageFile);
}

// bmfh contains some information about the bitmap file (about the file, not about the bitmap itself)
unsigned char*	createBitmapFileHeader(int height, int stride)
{
    int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);

    static unsigned char	fileHeader[] = {
        0,0,     /// Signature
        0,0,0,0, /// Image file size in bytes
        0,0,0,0, /// Reserved
        0,0,0,0, /// Start of pixel array
    };

    fileHeader[0] = (unsigned char)('B');
    fileHeader[1] = (unsigned char)('M');
    fileHeader[2] = (unsigned char)(fileSize);
    fileHeader[3] = (unsigned char)(fileSize >>  8);
    fileHeader[4] = (unsigned char)(fileSize >> 16);
    fileHeader[5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

    return (fileHeader);
}
// bmih contains information about the bitmap such as size, colors,... 
unsigned char*	createBitmapInfoHeader(int height, int width)
{
    static unsigned char	infoHeader[] = {
        0,0,0,0, /// Header size
        0,0,0,0, /// Image width
        0,0,0,0, /// Image height
        0,0,     /// Number of color planes
        0,0,     /// Bits per pixel
        0,0,0,0, /// Compression
        0,0,0,0, /// Image size
        0,0,0,0, /// Horizontal resolution
        0,0,0,0, /// Vertical resolution
        0,0,0,0, /// Colors in color table
        0,0,0,0, /// Important color count
    };

    infoHeader[0] = (unsigned char)(INFO_HEADER_SIZE);
    infoHeader[4] = (unsigned char)(width);
    infoHeader[5] = (unsigned char)(width >> 8);
    infoHeader[6] = (unsigned char)(width >> 16);
    infoHeader[7] = (unsigned char)(width >> 24);
    infoHeader[8] = (unsigned char)(height);
    infoHeader[9] = (unsigned char)(height >> 8);
    infoHeader[10] = (unsigned char)(height >> 16);
    infoHeader[11] = (unsigned char)(height >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(BYTES_PER_PIXEL * 8);

    return (infoHeader);
}
