/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_primitives.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:49:16 by njennes           #+#    #+#             */
/*   Updated: 2022/05/05 15:38:56 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	render_rect(t_vec2 pos, t_vec2 size, int color)
{
	int y;
	int x;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			mlx_pixel_put_img(x + pos.x, y + pos.y, color);
			x++;
		}
		y++;
	}
}

void	render_circle(t_vec2 pos, float diameter, int color)
{
	float	i;
	float	j;
	float	diameter_2;

	i = -diameter / 2;
	diameter_2 = (diameter / 2) * (diameter / 2);
	while (i < diameter / 2)
	{
		j = -diameter / 2;
		while (j < diameter / 2)
		{
			if (i * i + j * j < diameter_2)
				mlx_pixel_put_img(pos.x + j, pos.y + i, color);
			j++;
		}
		i++;
	}
}
