/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_font.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:33:19 by njennes           #+#    #+#             */
/*   Updated: 2022/05/21 18:14:42 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "render.h"
#include "colors.h"

static int	render_letter(char c, t_font *font, int size, t_ivec2 pos);
static void	render_bitmap_portion(t_font_bitmap *bitmap, t_ivec2 screen_pos,
	t_ivec2 pos, t_ivec2 size);

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

	if (c < 0)
		return ;
	infos = font->characters[(int)c];
	render_bitmap_portion(&font->bitmap,
		ivec2(pos.x + infos.x_off, pos.y + infos.y_off),
		ivec2(infos.x, infos.y),
		ivec2(infos.width, infos.height));
	return (infos.x_advance);
}

static void	render_bitmap_portion(t_font_bitmap *bitmap, t_ivec2 screen_pos,
	t_ivec2 pos, t_ivec2 size)
{
	int64_t	i;
	int64_t	j;
	uint8_t	*data;
	int		*px;

	data = bitmap->data + pos.x * bitmap->bpp / 8 + pos.y * bitmap->line_size;
	i = 0;
	while (i < size.y)
	{
		j = 0;
		while (j < size.x)
		{
			px = (int *)(data + j * bitmap->bpp / 8 + i * bitmap->line_size);
			if (get_t(*px) != 255)
				set_screen_pixel(screen_pos.x + j, screen_pos.y + i, *px);
			j++;
		}
		i++;
	}
}
