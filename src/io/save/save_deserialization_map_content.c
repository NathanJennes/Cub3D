/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialization_map_content.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 12:21:29 by njennes           #+#    #+#             */
/*   Updated: 2022/05/15 16:06:03 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"

inline static int	contains_illegal_char(t_map_info *infos, char *line);
inline static int	is_illegal_char(char c, t_map_info *infos, int *saw_wall,
						int *last_is_wall);

int	deserialize_map_parse_map_content(char *line, t_gamestate *save)
{
	t_map_info	*infos;

	infos = &save->map;
	line = ft_trimr(line);
	if (contains_illegal_char(infos, line))
		return (0);
	if (!infos->map_raw)
		infos->map_raw = gc_strarray_init();
	infos->map_raw = gc_strarray_append(infos->map_raw, line);
	if ((int64_t)ft_strlen(line) > infos->width)
		return (0);
	return (1);
}

inline static int	contains_illegal_char(t_map_info *infos, char *line)
{
	size_t	i;
	int		saw_wall;
	int		last_is_wall;

	i = 0;
	saw_wall = 0;
	last_is_wall = 0;
	while (line[i])
	{
		if (is_illegal_char(line[i], infos, &saw_wall, &last_is_wall))
			return (1);
		i++;
	}
	if (!saw_wall || !last_is_wall)
		return (1);
	return (0);
}

inline static int	is_illegal_char(char c, t_map_info *infos, int *saw_wall,
		int *last_is_wall)
{
	if (c == '1')
	{
		*saw_wall = 1;
		*last_is_wall = 1;
	}
	else if (ft_isalpha(c) && (!(c == 'W' || c == 'S' || c == 'N' || c == 'E')
			|| !saw_wall || infos->spawn_dir))
		return (1);
	else if (c != '0' && !ft_isalpha(c) && c != ' ')
		return (1);
	else
		*last_is_wall = 0;
	return (0);
}
