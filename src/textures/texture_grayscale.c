/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_grayscale.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 22:52:33 by njennes           #+#    #+#             */
/*   Updated: 2022/06/10 19:47:52 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "texture.h"
#include "mlx.h"
#include "colors.h"

void	create_texture_grayscale(t_texture *tex)
{
	size_t		tex_size;
	size_t		i;
	int			*pixel;
	int			*original_pixel;
	int			gray;

	tex->grayscale = (uint8_t *)mlx_get_data_addr(tex->grayscale_handle,
			&tex->bpp, &tex->line_size, &tex->endian);
	i = 0;
	tex_size = tex->width * tex->height;
	while (i < tex_size)
	{
		original_pixel = (int *)(tex->original + i * sizeof(int));
		pixel = (int *)(tex->grayscale + i * sizeof(int));
		gray = (get_r(*original_pixel) + get_g(*original_pixel)
				+ get_b(*original_pixel)) / 3;
		*pixel = trgb(get_t(*original_pixel), gray, gray, gray);
		i++;
	}
}

void	create_texture_inverse_grayscale(t_texture *tex)
{
	size_t	tex_size;
	size_t	i;
	int		*pixel;
	int		*original_pixel;
	int		gray;

	tex->inversed_grayscale = (uint8_t *)mlx_get_data_addr(
			tex->inversed_grayscale_handle, &tex->bpp,
			&tex->line_size, &tex->endian);
	i = 0;
	tex_size = tex->width * tex->height;
	while (i < tex_size)
	{
		original_pixel = (int *)(tex->original + i * sizeof(int));
		pixel = (int *)(tex->inversed_grayscale + i * sizeof(int));
		gray = (get_r(*original_pixel) + get_g(*original_pixel)
				+ get_b(*original_pixel)) / 3;
		*pixel = trgb(get_t(*original_pixel), 255 - gray, 255 - gray, 255 - gray);
		i++;
	}
}
