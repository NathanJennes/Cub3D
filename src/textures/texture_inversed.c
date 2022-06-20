/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_inversed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 23:11:31 by njennes           #+#    #+#             */
/*   Updated: 2022/06/20 14:18:42 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "mlx.h"
#include "core.h"

void	create_texture_inversed(t_texture *tex)
{
	int64_t		tex_size;
	int64_t		i;
	t_rgb		*pixel;
	t_rgb		original_pixel;

	tex->inversed = (t_rgb *)mlx_get_data_addr(tex->inversed_handle,
			&tex->bpp, &tex->line_size, &tex->endian);
	i = 0;
	tex_size = tex->width * tex->height;
	while (i < tex_size)
	{
		pixel = &tex->inversed[i];
		original_pixel = tex->original[i];
		pixel->r = 255 - original_pixel.r;
		pixel->g = 255 - original_pixel.g;
		pixel->b = 255 - original_pixel.b;
		i++;
	}
}
