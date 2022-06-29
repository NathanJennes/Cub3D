/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_primitives_img.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:17:28 by njennes           #+#    #+#             */
/*   Updated: 2022/06/24 15:26:38 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "core.h"
#include "render.h"

void	draw_rect_tex(t_ivec2 pos, t_ivec2 size, int color, int64_t tex_id)
{
	int	y;
	int	x;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			set_texture_pixel(x + pos.x, y + pos.y, color, tex_id);
			x++;
		}
		y++;
	}
}

void	draw_circle_tex(t_ivec2 pos, int64_t diameter, int col, int64_t tex_id)
{
	int64_t	i;
	int64_t	j;
	int64_t	diameter_2;
	int64_t	radius;

	radius = diameter / 2;
	i = -radius;
	diameter_2 = radius * radius;
	while (i <= radius)
	{
		j = -radius;
		while (j <= radius)
		{
			if (i * i + j * j <= diameter_2)
				set_texture_pixel(pos.x + j, pos.y + i, col, tex_id);
			j++;
		}
		i++;
	}
}

void	draw_line_tex(t_ivec2 start, t_ivec2 end, int col, int64_t tex_id)
{
	double	pixels_to_draw;
	double	pixels_drawn;
	t_vec2	ppos;
	t_vec2	delta;

	pixels_to_draw = sqrt((ft_pow2(end.x - start.x)) + \
			ft_pow2(end.y - start.y));
	delta.x = ((double)end.x - (float)start.x) / (float)pixels_to_draw;
	delta.y = ((float)end.y - (float)start.y) / (float)pixels_to_draw;
	ppos = iv2_to_v2(start);
	pixels_drawn = 0;
	while (pixels_drawn < pixels_to_draw)
	{
		vec2_add(&ppos, delta);
		set_texture_pixel(ppos.x, ppos.y, col, tex_id);
		pixels_drawn++;
	}
}

void	draw_line_lerp_tex(t_ivec2 start, t_ivec2 end,
			t_ivec2 col, int64_t tex_id)
{
	double	pixels_to_draw;
	double	pixels_drawn;
	t_vec2	ppos;
	t_vec2	delta;

	pixels_to_draw = sqrt((ft_pow2(end.x - start.x)) + \
			ft_pow2(end.y - start.y));
	delta.x = ((float)end.x - (float)start.x) / (float)pixels_to_draw;
	delta.y = ((float)end.y - (float)start.y) / (float)pixels_to_draw;
	ppos = iv2_to_v2(start);
	pixels_drawn = 0;
	while (pixels_drawn < pixels_to_draw)
	{
		vec2_add(&ppos, delta);
		set_texture_pixel(ppos.x, ppos.y,
			color_lerp(col.x, col.y, pixels_drawn / pixels_to_draw), tex_id);
		pixels_drawn++;
	}
}
