/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_font.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:33:19 by njennes           #+#    #+#             */
/*   Updated: 2022/05/21 19:45:37 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "render.h"
#include "colors.h"

static int	render_letter(char c, t_font *font, int size, t_ivec2 pos);
static int	sample_pixel(uint8_t *data, t_vec2 pos, t_vec2 size, int line_size);

void	render_text(char *text, char *font_name, int size, t_ivec2 pos)
{
	t_font	*font;
	size_t	i;
	size_t	len;
	int64_t	x_pos;

	if (!text || !font_name || size <= 0)
		return ;
	font = get_font(font_name);
	if (!font)
		return ;
	i = 0;
	len = ft_strlen(text);
	x_pos = pos.x;
	while (i < len)
	{
		x_pos += render_letter(text[i], font, size, ivec2(x_pos, pos.y));
		i++;
	}
}

static int	render_letter(char c, t_font *font, int size, t_ivec2 pos)
{
	t_char_meta	infos;
	t_ivec2		xy;
	t_ivec2		px_size;
	float		size_ratio;

	if (c < 0)
		return (0);
	infos = font->characters[(int)c];
	size_ratio = (float)size / (float)font->font_size;
	px_size = ivec2((int64_t)(size_ratio * (float)infos.width),
		(int64_t)(size_ratio * (float)infos.height));
	xy = ivec2(0, 0);
	while (xy.y < px_size.y)
	{
		xy.x = 0;
		while (xy.x < px_size.x)
		{
			int	color = sample_pixel(font->bitmap.data,
					vec2((float)infos.x + (float)xy.x / size_ratio,
					(float)infos.y + (float)xy.y / size_ratio),
					vec2(1.0f / size_ratio, 1.0f / size_ratio),
					font->bitmap.line_size);
			if (get_t(color) < 255)
				set_screen_pixel(infos.x_off * size_ratio + pos.x + xy.x,
					infos.y_off * size_ratio + pos.y + xy.y, color);
			xy.x++;
		}
		xy.y++;
	}
	return ((int)((float)infos.x_advance * size_ratio));
}

static int	sample_pixel(uint8_t *data, t_vec2 pos, t_vec2 size, int line_size)
{
	int		t;
	int		r;
	int		g;
	int		b;
	t_vec2	sample_dists;
	t_vec2	sampling_pos;
	t_ivec2	ij;

	sample_dists = vec2(size.x / (FONT_SAMPLING + 1.0f),
		size.y / (FONT_SAMPLING + 1.0f));
	t = 0;
	r = 0;
	g = 0;
	b = 0;
	ij = ivec2(0, 0);
	while (ij.y < FONT_SAMPLING)
	{
		ij.x = 0;
		while (ij.x < FONT_SAMPLING)
		{
			sampling_pos = vec2(pos.x + sample_dists.x + sample_dists.x * (float)ij.x,
				pos.y + sample_dists.y + sample_dists.y * (float)ij.y);
			t += get_t(*(int *)(data + (int)sampling_pos.x * sizeof (int)
								+ (int)sampling_pos.y * line_size));
			r += get_r(*(int *)(data + (int)sampling_pos.x * sizeof (int)
								+ (int)sampling_pos.y * line_size));
			g += get_g(*(int *)(data + (int)sampling_pos.x * sizeof (int)
								+ (int)sampling_pos.y * line_size));
			b += get_b(*(int *)(data + (int)sampling_pos.x * sizeof (int)
								+ (int)sampling_pos.y * line_size));
			ij.x++;
		}
		ij.y++;
	}
	return (trgb(t / (FONT_SAMPLING * FONT_SAMPLING), r / (FONT_SAMPLING * FONT_SAMPLING),
		g / (FONT_SAMPLING * FONT_SAMPLING), b / (FONT_SAMPLING * FONT_SAMPLING)));
}
