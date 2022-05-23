/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:47:30 by njennes           #+#    #+#             */
/*   Updated: 2022/05/23 14:18:12 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int64_t	get_text_width(char *text, char *font_name, int size)
{
	t_font	*font;
	int64_t	width;
	size_t	len;
	size_t	i;
	float	ratio;

	if (!text || !font_name || size <= 0)
		return (0);
	font = get_font(font_name);
	len = ft_strlen(text);
	if (!font || len == 0)
		return (0);
	ratio = (float)size / (float)font->font_size;
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
	return ((int64_t)((float)width * ratio));
}

int64_t	get_text_height(char *text, char *font_name, int size)
{
	t_font	*font;
	int64_t	height;
	size_t	len;
	size_t	i;
	float	ratio;

	if (!text || !font_name || size <= 0)
		return (0);
	font = get_font(font_name);
	len = ft_strlen(text);
	if (!font || len == 0)
		return (0);
	ratio = (float)size / (float)font->font_size;
	i = 0;
	height = 0;
	while (i < len - 1)
	{
		if (text[i] >= 0)
			height = ft_maxi(height, font->characters[(int)text[i]].height);
		i++;
	}
	return ((int64_t)((float)height * ratio));
}

t_ivec2	get_text_size(char *text, char *font_name, int size)
{
	t_ivec2	result;

	result.x = get_text_width(text, font_name, size);
	result.y = get_text_height(text, font_name, size);
	return (result);
}
