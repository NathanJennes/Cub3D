/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_generation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:58:17 by njennes           #+#    #+#             */
/*   Updated: 2022/06/15 13:39:38 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaky.h"
#include "texture.h"
#include "mlx.h"
#include "core.h"

void	create_texture_variations(t_texture *tex);

static void	transfer_texture_data(t_xpm_file *file, t_texture *texture);

t_texture	create_texture_from_xpm_file(t_xpm_file file)
{
	t_texture	texture;

	gc_memset(&texture, 0, sizeof (t_texture));
	transfer_texture_data(&file, &texture);
	create_texture_variations(&texture);
	return (texture);
}

t_texture	create_blank_texture(int width, int height)
{
	t_texture	texture;

	gc_memset(&texture, 0, sizeof (t_texture));
	texture.width = width;
	texture.height = height;
	texture.original_handle = mlx_new_image(get_mlx(), width, height);
	if (!texture.original_handle)
		return (texture);
	texture.original = (uint8_t *)mlx_get_data_addr(
			texture.original_handle, &texture.bpp,
			&texture.line_size, &texture.endian);
	gc_memseti(texture.original, trgb(255, 0, 0, 0),
		texture.width * texture.height);
	return (texture);
}

void	finish_new_texture(int64_t tex_id)
{
	t_texture	*tex;

	if (tex_id == INVALID_TEXTURE)
		return ;
	tex = get_texture_from_id(tex_id);
	if (!tex)
		return ;
	create_texture_variations(tex);
}

static void	transfer_texture_data(t_xpm_file *file, t_texture *texture)
{
	texture->original_handle = file->handle;
	texture->original = file->data;
	texture->width = file->width;
	texture->height = file->height;
	texture->bpp = file->bpp;
	texture->endian = file->endian;
	texture->line_size = file->line_size;
}
