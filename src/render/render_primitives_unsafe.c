/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_primitives_unsafe.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:49:16 by njennes           #+#    #+#             */
/*   Updated: 2022/05/26 16:21:38 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"

void	draw_rect_unsafe(t_ivec2 pos, t_ivec2 size, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			set_screen_pixel_unsafe(x + pos.x, y + pos.y, color);
			x++;
		}
		y++;
	}
}

void	draw_circle_unsafe(t_ivec2 pos, int64_t diameter, int color)
{
	int64_t	i;
	int64_t	j;
	int64_t	diameter_2;
	int64_t	radius;
	t_ivec2	ij2;

	radius = diameter / 2;
	i = -radius;
	diameter_2 = radius * radius;
	while (i < radius)
	{
		ij2.x = i * i;
		j = -radius;
		while (j < radius)
		{
			ij2.y = j * j;
			if (ij2.x + ij2.y < diameter_2)
				set_screen_pixel_unsafe(pos.x + j, pos.y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_line_unsafe(t_ivec2 start, t_ivec2 end, int col)
{
	double	pixels_to_draw;
	double	pixels_drawn;
	t_vec2	ppos;
	t_vec2	delta;

	pixels_to_draw = ft_sqrt((ft_pow2(end.x - start.x)) + \
			ft_pow2(end.y - start.y));
	delta.x = ((double)end.x - (double)start.x) / (double)pixels_to_draw;
	delta.y = ((double)end.y - (double)start.y) / (float)pixels_to_draw;
	ppos = iv2_to_v2(start);
	pixels_drawn = 0;
	while (pixels_drawn < pixels_to_draw)
	{
		vec2_add(&ppos, delta);
		set_screen_pixel_unsafe(ppos.x, ppos.y, col);
		pixels_drawn++;
	}
}

void	draw_line_lerp_unsafe(t_ivec2 start, t_ivec2 end, int col1, int col2)
{
	double	pixels_to_draw;
	double	pixels_drawn;
	t_vec2	ppos;
	t_vec2	delta;

	pixels_to_draw = ft_sqrt((ft_pow2(end.x - start.x)) + \
			ft_pow2(end.y - start.y));
	delta.x = ((float)end.x - (float)start.x) / (float)pixels_to_draw;
	delta.y = ((float)end.y - (float)start.y) / (float)pixels_to_draw;
	ppos = iv2_to_v2(start);
	pixels_drawn = 0;
	while (pixels_drawn < pixels_to_draw)
	{
		vec2_add(&ppos, delta);
		set_screen_pixel_unsafe(ppos.x, ppos.y,
			color_lerp(col1, col2, pixels_drawn / pixels_to_draw));
		pixels_drawn++;
	}
}
