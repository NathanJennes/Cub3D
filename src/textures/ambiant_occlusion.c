/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiant_occlusion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:08:31 by njennes           #+#    #+#             */
/*   Updated: 2022/05/09 22:51:30 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

static void	shade_pixel(uint8_t *data, int64_t row, int64_t total_row);

void	shade_ao_texture_flat(
		uint8_t *data, int width, int height, int bpp)
{
	int64_t	i;
	int64_t	total_size;
	int64_t	row;
	int64_t	pixel_size;

	pixel_size = bpp / 8;
	total_size = width * height;
	i = 0;
	while (i < total_size)
	{
		row = i / width;
		if (row <= height / 10)
			shade_pixel(&data[i * pixel_size], row, height / 10);
		else if (row >= height - height / 10)
			shade_pixel(&data[i * pixel_size], height - row, height / 10);
		i++;
	}
}

void	shade_ao_texture_right(
		uint8_t *data, int width, int height, int bpp)
{
	int64_t	i;
	int64_t	total_size;
	int64_t	column;
	int64_t	pixel_size;

	pixel_size = bpp / 8;
	total_size = width * height;
	i = 0;
	while (i < total_size)
	{
		column = i % width;
		if (column >= width - width / 10)
			shade_pixel(&data[i * pixel_size], width - column, width / 10);
		i++;
	}
}

void	shade_ao_texture_left(
		uint8_t *data, int width, int height, int bpp)
{
	int64_t	i;
	int64_t	total_size;
	int64_t	column;
	int64_t	pixel_size;

	pixel_size = bpp / 8;
	total_size = width * height;
	i = 0;
	while (i < total_size)
	{
		column = i % width;
		if (column <= width / 10)
			shade_pixel(&data[i * pixel_size], column, width / 10);
		i++;
	}
}

void	shade_ao_texture_all(
		uint8_t *data, int width, int height, int bpp)
{
	shade_ao_texture_flat(data, width, height, bpp);
	shade_ao_texture_right(data, width, height, bpp);
	shade_ao_texture_left(data, width, height, bpp);
}

static void	shade_pixel(uint8_t *data, int64_t row, int64_t total_row)
{
	double	shade_factor;

	shade_factor = (double)row / (double)total_row;
	data[0] *= shade_factor;
	data[1] *= shade_factor;
	data[2] *= shade_factor;
}
