/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_generation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:58:17 by njennes           #+#    #+#             */
/*   Updated: 2022/05/14 15:57:42 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaky.h"
#include "texture.h"

void		shade_ao_texture_flat(
				uint8_t *data, int width, int height, int bpp);
void		shade_ao_texture_right(
				uint8_t *data, int width, int height, int bpp);
void		shade_ao_texture_left(
				uint8_t *data, int width, int height, int bpp);
void		shade_ao_texture_all(
				uint8_t *data, int width, int height, int bpp);

static void	transfer_texture_data(t_xpm_file *file, t_texture *texture);
static void	create_texture_variations(t_texture *tex);

t_texture	create_texture_from_xpm_file(t_xpm_file file)
{
	t_texture	texture;

	gc_memset(&texture, 0, sizeof (t_texture));
	transfer_texture_data(&file, &texture);
	create_texture_variations(&texture);
	return (texture);
}

static void	create_texture_variations(t_texture *tex)
{
	tex->ao_flat = gc_calloc(tex->width * tex->height, tex->bpp);
	tex->ao_right = gc_calloc(tex->width * tex->height, tex->bpp);
	tex->ao_left = gc_calloc(tex->width * tex->height, tex->bpp);
	tex->ao_all = gc_calloc(tex->width * tex->height, tex->bpp);
	shade_ao_texture_flat(tex->ao_flat, tex->width, tex->height, tex->bpp);
	shade_ao_texture_right(tex->ao_right, tex->width, tex->height, tex->bpp);
	shade_ao_texture_left(tex->ao_left, tex->width, tex->height, tex->bpp);
	shade_ao_texture_all(tex->ao_all, tex->width, tex->height, tex->bpp);
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