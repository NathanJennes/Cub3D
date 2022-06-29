/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_grayscale.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 22:52:33 by njennes           #+#    #+#             */
/*   Updated: 2022/06/24 14:55:05 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "texture.h"
#include "mlx.h"
#include "colors.h"
#include "core.h"

void	create_texture_grayscale(t_texture *tex)
{
	size_t	tex_size;
	size_t	i;
	t_rgb	*pixel;
	t_rgb	original_pixel;
	int		gray;

	tex->grayscale = (t_rgb *)mlx_get_data_addr(
			tex->grayscale_handle, &tex->bpp,
			&tex->line_size, &tex->endian);
	i = 0;
	tex_size = tex->width * tex->height;
	while (i < tex_size)
	{
		original_pixel = tex->original[i];
		pixel = &tex->grayscale[i];
		gray = (original_pixel.r + original_pixel.g
				+ original_pixel.b) / 3;
		pixel->r = gray;
		pixel->g = gray;
		pixel->b = gray;
		pixel->t = original_pixel.t;
		i++;
	}
}

void	create_texture_inverse_grayscale(t_texture *tex)
{
	size_t	tex_size;
	size_t	i;
	t_rgb	*pixel;
	t_rgb	original_pixel;
	int		gray;

	tex->inversed_grayscale = (t_rgb *)mlx_get_data_addr(
			tex->inversed_grayscale_handle, &tex->bpp,
			&tex->line_size, &tex->endian);
	i = 0;
	tex_size = tex->width * tex->height;
	while (i < tex_size)
	{
		original_pixel = tex->original[i];
		pixel = &tex->inversed_grayscale[i];
		gray = (original_pixel.r + original_pixel.g
				+ original_pixel.b) / 3;
		pixel->r = 255 - gray;
		pixel->g = 255 - gray;
		pixel->b = 255 - gray;
		pixel->t = original_pixel.t;
		i++;
	}
}
