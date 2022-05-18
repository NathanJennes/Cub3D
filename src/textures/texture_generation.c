/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_generation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:58:17 by njennes           #+#    #+#             */
/*   Updated: 2022/05/18 17:18:05 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaky.h"
#include "texture.h"
#include "mlx.h"
#include "core.h"
#include "render.h"

void		shade_ao_texture_flat(
				uint8_t *data, int width, int height, int bpp);
void		shade_ao_texture_right(
				uint8_t *data, int width, int height, int bpp);
void		shade_ao_texture_left(
				uint8_t *data, int width, int height, int bpp);
void		shade_ao_texture_all(
				uint8_t *data, int width, int height, int bpp);
void		create_texture_grayscale(t_texture *tex);
void		create_texture_inversed(t_texture *tex);
void		create_texture_inverse_grayscale(t_texture *tex);

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

t_texture	create_blank_texture(int width, int height)
{
	t_texture	texture;

	gc_memset(&texture, 0, sizeof (t_texture));
	texture.width = width;
	texture.height = height;
	texture.original_handle = mlx_new_image(get_mlx(), width, height);
	if (!texture.original_handle)
		return (texture);
	texture.original = (uint8_t *)mlx_get_data_addr(texture.original_handle, &texture.bpp,
					&texture.line_size, &texture.endian);
	gc_memseti(texture.original, trgb(0, 80, 215, 50), texture.width * texture.height);
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
	tex->grayscale_handle = mlx_new_image(get_mlx(), tex->width, tex->height);
	tex->inversed_handle = mlx_new_image(get_mlx(), tex->width, tex->height);
	tex->inversed_grayscale_handle = mlx_new_image(get_mlx(), tex->width, tex->height);
	create_texture_grayscale(tex);
	create_texture_inversed(tex);
	create_texture_inverse_grayscale(tex);
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
