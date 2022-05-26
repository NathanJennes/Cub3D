/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:47:30 by njennes           #+#    #+#             */
/*   Updated: 2022/05/23 16:03:43 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static int64_t	get_min_y_offset(char *text, char *font_name, int size);
static int64_t	get_max_y_offset(char *text, char *font_name, int size);

int64_t	get_text_width(char *text, char *font_name, int size)
{
	t_font	*font;
	int64_t	width;
	size_t	len;
	size_t	i;
	double	ratio;

	if (!text || !font_name || size <= 0)
		return (0);
	font = get_font(font_name);
	len = ft_strlen(text);
	if (!font || len == 0)
		return (0);
	ratio = (double)size / (double)font->font_size;
	i = 0;
	width = 0;
	while (i < len - 1)
	{
		if (text[i] >= 0)
			width += font->characters[(int)text[i]].x_advance;
		i++;
	}
	if (text[i] >= 0)
		width += font->characters[(int)text[i]].width;
	return ((int64_t)((double)width * ratio));
}

static int64_t	get_min_y_offset(char *text, char *font_name, int size)
{
	t_font	*font;
	int64_t	y_offset;
	size_t	len;
	size_t	i;
	double	ratio;

	if (!text || !font_name || size <= 0)
		return (0);
	font = get_font(font_name);
	len = ft_strlen(text);
	if (!font || len == 0)
		return (0);
	ratio = (double)size / (double)font->font_size;
	y_offset = font->characters[(int)text[0]].y_off;
	i = 1;
	while (i < len)
	{
		if (text[i] > ' ')
			y_offset = ft_mini(y_offset, font->characters[(int)text[i]].y_off);
		i++;
	}
	return ((int64_t)((double)y_offset * ratio));
}

static int64_t	get_max_y_offset(char *text, char *font_name, int size)
{
	t_font	*font;
	int64_t	y_offset;
	size_t	len;
	size_t	i;
	double	ratio;

	if (!text || !font_name || size <= 0)
		return (0);
	font = get_font(font_name);
	len = ft_strlen(text);
	if (!font || len == 0)
		return (0);
	ratio = (double)size / (double)font->font_size;
	y_offset = font->characters[(int)text[0]].y_off
		+ font->characters[(int)text[0]].height;
	i = 1;
	while (i < len)
	{
		if (text[i] > ' ')
			y_offset = ft_maxi(y_offset, font->characters[(int)text[i]].y_off
					+ font->characters[(int)text[i]].height);
		i++;
	}
	return ((int64_t)((double)y_offset * ratio));
}

int64_t	get_text_height(char *text, char *font_name, int size)
{
	int64_t	min_off;
	int64_t	max_off;

	min_off = get_min_y_offset(text, font_name, size);
	max_off = get_max_y_offset(text, font_name, size);
	return (max_off - min_off);
}

t_ivec2	get_text_size(char *text, char *font_name, int size)
{
	t_ivec2	result;

	result.x = get_text_width(text, font_name, size);
	result.y = get_text_height(text, font_name, size);
	return (result);
}
