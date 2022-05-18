/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_rendering.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:22:25 by njennes           #+#    #+#             */
/*   Updated: 2022/05/18 16:44:08 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "bool.h"

static int	pixel_in_texture(int64_t x, int64_t y, int width, int height);

void	clear_texture(int color, int64_t tex_id)
{
	int			i;
	int			total;
	int			bytes_pp;
	t_texture	*texture;

	texture = get_texture_from_id(tex_id);
	if (!texture)
		return ;
	i = 0;
	total = (texture->width * texture->height);
	bytes_pp = texture->bpp / 8;
	while (i < total)
	{
		*((unsigned int *)(texture->original + i * bytes_pp)) = color;
		i++;
	}
}

void	set_texture_pixel(int64_t x, int64_t y, int color, int64_t tex_id)
{
	uint8_t	*dst;
	t_texture	*texture;

	texture = get_texture_from_id(tex_id);
	if (!texture)
		return ;
	if (!pixel_in_texture(x, y, texture->width, texture->height))
		return ;
	dst = texture->original
		  + (y * texture->line_size + x * (texture->bpp / 8));
	*(unsigned int *)dst = color;
}

static t_bool	pixel_in_texture(int64_t x, int64_t y, int width, int height)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return (FALSE);
	return (TRUE);
}
