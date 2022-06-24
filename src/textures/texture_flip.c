/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_flip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 23:11:31 by njennes           #+#    #+#             */
/*   Updated: 2022/06/24 15:09:17 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	create_texture_wall(t_texture *tex)
{
	int64_t		column;
	int64_t		row;
	t_rgb		px;

	column = 0;
	while (column < tex->width)
	{
		row = 0;
		while (row < tex->height)
		{
			px = tex->original[column + row * tex->width];
			tex->wall_flip[column][row] = px;
			row++;
		}
		column++;
	}
}

void	create_texture_vflip(t_texture *tex)
{
	int64_t		column;
	int64_t		row;
	t_rgb		px;

	column = 0;
	while (column < tex->width)
	{
		row = 0;
		while (row < tex->height)
		{
			px = tex->wall[tex->width - column - 1][row];
			tex->wall_flip[column][row] = px;
			row++;
		}
		column++;
	}
}
