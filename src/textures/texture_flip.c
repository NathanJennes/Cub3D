/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_inverted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyril <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 23:11:31 by njennes           #+#    #+#             */
/*   Updated: 2022/06/06 01:18:01 by Cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"

void	create_texture_vflip(t_texture *tex)
{
	int64_t		i;
	int64_t		j;
	int64_t		px;
	int			*pixel;
	int			*original_pixel;

	i = 0;
	px = 0;
	while (i < tex->height)
	{
		j = tex->width - 1;
		while (j >= 0)
		{
			pixel = (int *)(tex->vflip + px * sizeof(int));
			original_pixel = (int *)
					(tex->original + (i * tex->line_size) + j * sizeof(int));
			*pixel = *original_pixel;
			j--;
			px++;
		}
		i++;
	}
}
