/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_deletion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 22:57:27 by njennes           #+#    #+#             */
/*   Updated: 2022/06/24 15:04:25 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "mlx.h"
#include "core.h"

void	free_texture(t_texture *texture)
{
	gc_free2d((void **)texture->wall, texture->width);
	gc_free2d((void **)texture->wall_flip, texture->width);
	gc_free(texture->name);
	if (texture->original_handle)
		mlx_destroy_image(get_mlx(), texture->original_handle);
	if (texture->grayscale_handle)
		mlx_destroy_image(get_mlx(), texture->grayscale_handle);
	if (texture->inversed_handle)
		mlx_destroy_image(get_mlx(), texture->inversed_handle);
	if (texture->inversed_grayscale_handle)
		mlx_destroy_image(get_mlx(), texture->inversed_grayscale_handle);
	ft_memset(texture, 0, sizeof(t_texture));
}
