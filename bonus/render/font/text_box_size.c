/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_box_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:39:28 by njennes           #+#    #+#             */
/*   Updated: 2022/05/23 16:03:10 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_ivec2	get_text_box_size(char *text, char *font_name, int size)
{
	t_ivec2	result;

	result.x = get_text_width(text, font_name, size);
	result.y = get_text_box_height(text, font_name, size);
	return (result);
}

int64_t	get_text_box_height(char *text, char *font_name, int size)
{
	t_font	*font;
	int64_t	height;
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
	height = 0;
	while (i < len - 1)
	{
		if (text[i] >= 0)
			height = ft_maxi(height, font->characters[(int)text[i]].height
					+ font->characters[(int)text[i]].y_off);
		i++;
	}
	return ((int64_t)((double)height * ratio));
}
