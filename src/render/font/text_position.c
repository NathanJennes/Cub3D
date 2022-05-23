/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_position.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:19:40 by njennes           #+#    #+#             */
/*   Updated: 2022/05/23 15:18:12 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_ivec2	text_center_height(char *text, char *font_name, int size, t_ivec2 pos)
{
	int64_t	box_height;
	int64_t	height;

	box_height = get_text_box_height(text, font_name, size);
	height = get_text_height(text, font_name, size);
	return (ivec2(pos.x, pos.y - height / 2 - (box_height - height)));
}

t_ivec2	text_center_width(char *text, char *font_name, int size, t_ivec2 pos)
{
	int64_t	width;

	width = get_text_width(text, font_name, size);
	return (ivec2(pos.x - width / 2, pos.y));
}

t_ivec2	text_center(char *text, char *font_name, int size, t_ivec2 pos)
{
	t_ivec2	result;

	result.x = text_center_width(text, font_name, size, pos).x;
	result.y = text_center_height(text, font_name, size, pos).y;
	return (result);
}
