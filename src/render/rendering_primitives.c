/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_primitives.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:49:16 by njennes           #+#    #+#             */
/*   Updated: 2022/05/05 16:04:43 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"

void	render_rect(t_vec2 pos, t_vec2 size, int color)
{
	int	y;
	int	x;

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

void	render_line(t_vec2 start, t_vec2 end, int col1, int col2)
{
	double	pixels_to_draw;
	double	pixels_drawn;
	t_vec2	ppos;
	t_vec2	delta;

	pixels_to_draw = ft_sqrt((ft_pow2(end.x - start.x)) + \
			ft_pow2(end.y - start.y));
	delta.x = (end.x - start.x) / pixels_to_draw;
	delta.y = (end.y - start.y) / pixels_to_draw;
	ppos = vec2(start.x, start.y);
	pixels_drawn = 0;
	while (pixels_drawn < pixels_to_draw)
	{
		vec2_add(&ppos, delta);
		mlx_pixel_put_img(ppos.x, ppos.y,
			color_lerp(col1, col2, pixels_drawn / pixels_to_draw));
		pixels_drawn++;
	}
}
