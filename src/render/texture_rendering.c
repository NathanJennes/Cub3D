/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_rendering.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:22:25 by njennes           #+#    #+#             */
/*   Updated: 2022/05/26 16:26:22 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "bool.h"

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
		*((unsigned int *)(texture->original + i * 4)) = color;
		i++;
	}
}

void	set_texture_pixel(int64_t x, int64_t y, int color, int64_t tex_id)
{
	uint8_t		*dst;
	t_texture	*texture;

	texture = get_texture_from_id(tex_id);
	if (!texture)
		return ;
	if (!pixel_in_texture(x, y, texture->width, texture->height))
		return ;
	dst = texture->original
		+ (y * texture->line_size + x * 4);
	*(unsigned int *)dst = color;
}

void	set_texture_pixel_unsafe(int64_t x, int64_t y,
	int color, int64_t tex_id)
{
	uint8_t		*dst;
	t_texture	*texture;

	texture = get_texture_from_id(tex_id);
	if (!texture)
		return ;
	dst = texture->original
		+ (y * texture->line_size + x * 4);
	*(unsigned int *)dst = color;
}

inline static t_bool	pixel_in_texture(int64_t x, int64_t y, int width, int height)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return (FALSE);
	return (TRUE);
}
