/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_deserialization.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 11:05:43 by njennes           #+#    #+#             */
/*   Updated: 2022/06/24 16:06:16 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "core.h"

void		construct_map(t_map_info *infos);
int			load_mandatory_map(t_gamestate *save_out, int fd, char *line,
				char *filename);

int	deserialize_save(t_gamestate *save_out, int fd, char *filename)
{
	char	*line;

	line = gc_get_next_line(fd);
	if (!line)
		return (0);
	line = ft_trimr(line);
	return (load_mandatory_map(save_out, fd, line, filename));
}
