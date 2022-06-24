/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiant_occlusion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:08:31 by njennes           #+#    #+#             */
/*   Updated: 2022/06/24 14:30:42 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "core.h"

inline static void	shade_pixel(t_rgb *data, int64_t row, int64_t total_row);

void	shade_ao_texture_flat(t_rgb **data, int width, int height)
{
	int64_t	row;
	int64_t	column;

	column = 0;
	while (column < width)
	{
		row = 0;
		while (row < height)
		{
			if (row <= height / 20)
				shade_pixel(&data[column][row], row, height / 20);
			else if (row >= height - height / 20)
				shade_pixel(&data[column][row], height - row, height / 20);
			row++;
		}
		column++;
	}
}

void	shade_ao_texture_right(t_rgb **data, int width, int height)
{
	int64_t	row;
	int64_t	column;

	column = 0;
	while (column < width)
	{
		row = 0;
		while (row < height)
		{
			if (column >= width - width / 20)
				shade_pixel(&data[column][row], width - column, width / 20);
			row++;
		}
		column++;
	}
}

void	shade_ao_texture_left(t_rgb **data, int width, int height)
{
	int64_t	row;
	int64_t	column;

	column = 0;
	while (column < width)
	{
		row = 0;
		while (row < height)
		{
			if (column <= width / 20)
				shade_pixel(&data[column][row], column, width / 20);
			row++;
		}
		column++;
	}
}

void	shade_ao_texture_all(t_rgb **data, int width, int height)
{
	shade_ao_texture_flat(data, width, height);
	shade_ao_texture_right(data, width, height);
	shade_ao_texture_left(data, width, height);
}

inline static void	shade_pixel(t_rgb *data, int64_t row, int64_t total_row)
{
	double	shade_factor;

	shade_factor = ft_lerpf(0.2, 1.0, (double)row / (double)total_row);
	data->r *= shade_factor;
	data->g *= shade_factor;
	data->b *= shade_factor;
}
