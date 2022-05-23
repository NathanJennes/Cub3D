/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_font_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:33:19 by njennes           #+#    #+#             */
/*   Updated: 2022/05/23 13:45:34 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "render.h"
#include "colors.h"

static int	render_letter(char c, t_font *font, t_ivec2 pos, t_ivec2 size_tex);
static int	sample_pixel(uint8_t *data, t_vec2 pos, t_vec2 size, int line_size);
static int	get_pixel_color(t_text_render *infos);
static void	render_pixel(t_text_render *infos, int color, int64_t tex_id);

void	render_text_tex(char *text, char *font_name, t_ivec2 pos,
			t_ivec2 size_id)
{
	t_font	*font;
	size_t	i;
	size_t	len;
	int64_t	x_pos;

	if (!text || !font_name || size_id.x <= 0)
		return ;
	font = get_font(font_name);
	if (!font)
		return ;
	i = 0;
	len = ft_strlen(text);
	x_pos = pos.x;
	while (i < len)
	{
		x_pos += render_letter(text[i], font, size_id, ivec2(x_pos, pos.y));
		i++;
	}
}

static int	render_letter(char c, t_font *font, t_ivec2 pos, t_ivec2 size_tex)
{
	t_text_render	infos;
	int				color;

	if (c < 0)
		return (0);
	infos.c = &font->characters[(int)c];
	infos.ratio = (float)size_tex.x / (float)font->font_size;
	infos.px_size = ivec2((int64_t)(infos.ratio * (float)infos.c->width),
			(int64_t)(infos.ratio * (float)infos.c->height));
	infos.xy = ivec2(0, 0);
	infos.font = font;
	infos.bitmap = &font->bitmap;
	infos.pos = pos;
	while (infos.xy.y < infos.px_size.y)
	{
		infos.xy.x = 0;
		while (infos.xy.x < infos.px_size.x)
		{
			color = get_pixel_color(&infos);
			render_pixel(&infos, color, size_tex.y);
			infos.xy.x++;
		}
		infos.xy.y++;
	}
	return ((int)((float)infos.c->x_advance * infos.ratio));
}

static int	get_pixel_color(t_text_render *infos)
{
	int	color;

	color = sample_pixel(infos->font->bitmap.data,
			vec2((float)infos->c->x + (float) infos->xy.x / infos->ratio,
				(float)infos->c->y + (float) infos->xy.y / infos->ratio),
			vec2(1.0f / infos->ratio, 1.0f / infos->ratio),
			infos->bitmap->line_size);
	return (color);
}

static void	render_pixel(t_text_render *infos, int color, int64_t tex_id)
{
	if (get_t(color) < 255)
		set_texture_pixel((int)((float)infos->c->x_off * infos->ratio)
			+ infos->pos.x + infos->xy.x,
			(int)((float)infos->c->y_off * infos->ratio)
			+ infos->pos.y + infos->xy.y, color, tex_id);
}

static int	sample_pixel(uint8_t *data, t_vec2 pos, t_vec2 size, int line_size)
{
	int64_t	t;
	t_vec2	sample_dists;
	t_vec2	sampling_pos;
	t_ivec2	ij;

	sample_dists = vec2(size.x / (FONT_SAMPLING + 1.0f),
			size.y / (FONT_SAMPLING + 1.0f));
	t = 0;
	ij = ivec2(0, 0);
	while (ij.y < FONT_SAMPLING)
	{
		ij.x = 0;
		while (ij.x < FONT_SAMPLING)
		{
			sampling_pos = vec2(pos.x + sample_dists.x
					+ sample_dists.x * (float)ij.x,
					pos.y + sample_dists.y + sample_dists.y * (float)ij.y);
			t += 255 - get_r(*(int *)(data + (int)sampling_pos.x * sizeof (int)
						+ (int)sampling_pos.y * line_size));
			ij.x++;
		}
		ij.y++;
	}
	return (trgb((int)(t / (FONT_SAMPLING * FONT_SAMPLING)), 255, 255, 255));
}
