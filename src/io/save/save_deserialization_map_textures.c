/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialization_map_textures.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 12:03:22 by njennes           #+#    #+#             */
/*   Updated: 2022/05/15 12:17:06 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"

int	deserialize_map_parse_no_tex(char *line, t_gamestate *save)
{
	char	*cursor;

	cursor = ft_trimr(line);
	cursor += ft_strlen("NO_TEX");
	cursor = ft_strskip_space(cursor);
	if (ft_strlen(cursor) == 0)
		return (0);
//	else if (ft_strncmp(cursor, "(null)", ft_strlen("(null)")) == 0)
//		save->map.no_tex = NULL;
//	else
//		save->map.no_tex = gc_strdup(cursor);
	return (1);
}

int	deserialize_map_parse_ea_tex(char *line, t_gamestate *save)
{
	char	*cursor;

	cursor = ft_trimr(line);
	cursor += ft_strlen("EA_TEX");
	cursor = ft_strskip_space(cursor);
	if (ft_strlen(cursor) == 0)
		return (0);
//	else if (ft_strncmp(cursor, "(null)", ft_strlen("(null)")) == 0)
//		save->map.ea_tex = NULL;
//	else
//		save->map.ea_tex = gc_strdup(cursor);
	return (1);
}

int	deserialize_map_parse_so_tex(char *line, t_gamestate *save)
{
	char	*cursor;

	cursor = ft_trimr(line);
	cursor += ft_strlen("SO_TEX");
	cursor = ft_strskip_space(cursor);
	if (ft_strlen(cursor) == 0)
		return (0);
//	else if (ft_strncmp(cursor, "(null)", ft_strlen("(null)")) == 0)
//		save->map.so_tex = NULL;
//	else
//		save->map.so_tex = gc_strdup(cursor);
	return (1);
}

int	deserialize_map_parse_we_tex(char *line, t_gamestate *save)
{
	char	*cursor;

	cursor = ft_trimr(line);
	cursor += ft_strlen("WE_TEX");
	cursor = ft_strskip_space(cursor);
	if (ft_strlen(cursor) == 0)
		return (0);
//	else if (ft_strncmp(cursor, "(null)", ft_strlen("(null)")) == 0)
//		save->map.we_tex = NULL;
//	else
//		save->map.we_tex = gc_strdup(cursor);
	return (1);
}
