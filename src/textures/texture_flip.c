/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_flip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 23:11:31 by njennes           #+#    #+#             */
/*   Updated: 2022/06/15 14:18:57 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	create_texture_vflip(t_rgb **original, t_rgb **vflip, int width, int height)
{
	int64_t		column;
	int64_t		row;
	t_rgb		px;

	column = 0;
	while (column < width)
	{
		row = 0;
		while (row < height)
		{
			px = original[width - column - 1][row];
			vflip[column][row] = px;
			row++;
		}
		column++;
	}
}
