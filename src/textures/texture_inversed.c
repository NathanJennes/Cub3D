/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_inversed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 23:11:31 by njennes           #+#    #+#             */
/*   Updated: 2022/05/20 15:40:50 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "texture.h"
#include "mlx.h"
#include "colors.h"

void	create_texture_inversed(t_texture *tex)
{
	size_t		tex_size;
	size_t		i;
	int			*pixel;
	int			*original_pixel;

	tex->inversed = (uint8_t *)mlx_get_data_addr(tex->inversed_handle,
			&tex->bpp, &tex->line_size, &tex->endian);
	i = 0;
	tex_size = tex->width * tex->height;
	while (i < tex_size)
	{
		pixel = (int *)(tex->inversed + i * sizeof(int));
		original_pixel = (int *)(tex->original + i * sizeof(int));
		*pixel = trgb(get_t(*original_pixel), 255 - get_r(*original_pixel),
				255 - get_g(*original_pixel), 255 - get_b(*original_pixel));
		i++;
	}
}
