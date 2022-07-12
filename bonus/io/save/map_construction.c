/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_construction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:24:49 by njennes           #+#    #+#             */
/*   Updated: 2022/06/27 15:17:25 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

inline static void	read_map_content(t_map_info *infos, size_t i, size_t j,
						int *row);

void	construct_map(t_map_info *infos)
{
	int64_t	i;
	int64_t	j;
	int		*row;

	infos->map = gc_calloc(infos->height, sizeof (int *));
	i = 0;
	while (i < infos->height)
	{
		row = gc_calloc(infos->width, sizeof (int));
		ft_memseti(row, VOID, infos->width);
		j = 0;
		while (j < (int64_t)ft_strlen(infos->map_raw[i]))
		{
			read_map_content(infos, i, j, row);
			j++;
		}
		infos->map[i++] = row;
	}
}

inline static void	read_map_content(t_map_info *infos, size_t i, size_t j,
			int *row)
{
	if (infos->map_raw[i][j] == '1')
		row[j] = WALL;
	else if (infos->map_raw[i][j] == '0' || ft_isalpha(infos->map_raw[i][j]))
		row[j] = EMPTY;
	else if (infos->map_raw[i][j] == ' ')
		row[j] = VOID;
	if (ft_isalpha(infos->map_raw[i][j]))
	{
		infos->spawn_dir = infos->map_raw[i][j];
		infos->spawn_pos = vec2((double)j * CELL_SIZE + CELL_SIZE / 2.0,
				(double)i * CELL_SIZE + CELL_SIZE / 2.0);
	}
}
