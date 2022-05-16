/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_deletion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 22:57:27 by njennes           #+#    #+#             */
/*   Updated: 2022/05/09 23:01:25 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "leaky.h"
#include "mlx.h"
#include "core.h"

void	free_texture(t_texture *texture)
{
	gc_free(texture->ao_all);
	gc_free(texture->ao_right);
	gc_free(texture->ao_left);
	gc_free(texture->ao_flat);
	mlx_destroy_image(get_mlx(), texture->original_handle);
	mlx_destroy_image(get_mlx(), texture->grayscale_handle);
	mlx_destroy_image(get_mlx(), texture->inversed_handle);
	mlx_destroy_image(get_mlx(), texture->inversed_grayscale_handle);
	gc_memset(texture, 0, sizeof(t_texture));
}
