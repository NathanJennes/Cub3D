/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_primitives_img_unsafe.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:17:28 by njennes           #+#    #+#             */
/*   Updated: 2022/06/27 17:08:02 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "core.h"
#include "render.h"

static void	divide_by_two(t_ivec2 *pos, t_ivec2 *size);

void	draw_rect_tex_unsafe(t_ivec2 pos, t_ivec2 size, int color,
			int64_t tex_id)
{
	t_ivec2		iter;
	int64_t		*pixels;
	int64_t		col;
	t_texture	*tex;
	int64_t		width2;

	tex = get_texture_from_id(tex_id);
	if (!tex)
		return ;
	pixels = (int64_t *)tex->original;
	divide_by_two(&pos, &size);
	((int *)&col)[0] = color;
	((int *)&col)[1] = color;
	width2 = tex->width / 2;
	iter = ivec2_zero();
	while (iter.y < size.y)
	{
		iter.x = 0;
		while (iter.x < size.x)
		{
			pixels[pos.x + iter.x + (pos.y + iter.y) * width2] = col;
			iter.x++;
		}
		iter.y++;
	}
}

static void	divide_by_two(t_ivec2 *pos, t_ivec2 *size)
{
	(*size).x /= 2;
	(*pos).x /= 2;
}

void	draw_circle_tex_unsafe(t_ivec2 pos, int64_t diameter,
	int col, int64_t tex_id)
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
				set_texture_pixel_unsafe(pos.x + j, pos.y + i, col, tex_id);
			j++;
		}
		i++;
	}
}

void	draw_line_tex_unsafe(t_ivec2 start, t_ivec2 end,
	int col, int64_t tex_id)
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
		set_texture_pixel_unsafe(ppos.x, ppos.y, col, tex_id);
		pixels_drawn++;
	}
}

void	draw_line_lerp_tex_unsafe(t_ivec2 start, t_ivec2 end,
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
		set_texture_pixel_unsafe(ppos.x, ppos.y,
			color_lerp(col.x, col.y, pixels_drawn / pixels_to_draw), tex_id);
		pixels_drawn++;
	}
}
