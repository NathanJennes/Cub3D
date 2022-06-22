/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_rendering.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:22:25 by njennes           #+#    #+#             */
/*   Updated: 2022/06/20 14:35:57 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "bool.h"
#include "core.h"

inline static int	pixel_in_texture(int64_t x, int64_t y, int width, int height);

void	clear_texture(int color, int64_t tex_id)
{
	int			i;
	int			total;
	t_texture	*texture;

	texture = get_texture_from_id(tex_id);
	if (!texture)
		return ;
	i = 0;
	total = (texture->width * texture->height);
	while (i < total)
	{
		texture->original[i].color = color;
		i++;
	}
}

void	set_texture_pixel(int64_t x, int64_t y, int color, int64_t tex_id)
{
	t_rgb		*dst;
	t_texture	*texture;

	texture = get_texture_from_id(tex_id);
	if (!texture)
		return ;
	if (!pixel_in_texture(x, y, texture->width, texture->height))
		return ;
	dst = &texture->original[x + y * texture->width];
	dst->color = color;
}

void	set_texture_pixel_unsafe(int64_t x, int64_t y,
	int color, int64_t tex_id)
{
	t_rgb		*dst;
	t_texture	*texture;

	texture = get_texture_from_id(tex_id);
	if (!texture)
		return ;
	dst = &texture->original[x + y * texture->width];
	dst->color = color;
}

inline static t_bool	pixel_in_texture(int64_t x, int64_t y, int width, int height)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return (FALSE);
	return (TRUE);
}
