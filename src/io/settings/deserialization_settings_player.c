/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialization_settings_player.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:12:28 by njennes           #+#    #+#             */
/*   Updated: 2022/06/26 17:27:35 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"

int	parse_fov(char *line, t_settings *settings)
{
	char	*line_cursor;

	line_cursor = ft_trimr(line);
	line_cursor = ft_strchr(line_cursor, ' ');
	if (!line_cursor)
		return (0);
	line_cursor = ft_strskip_space(line_cursor);
	if (!ft_isdigit(*line_cursor) || *line_cursor == '-')
		return (0);
	settings->fov = ft_atoi(line_cursor);
	if (settings->fov <= 0)
		return (0);
	line_cursor = ft_strskip_digit(line_cursor);
	if (ft_strlen(ft_strskip_space(line_cursor)) > 0)
		return (0);
	return (1);
}

int	parse_sens(char *line, t_settings *settings)
{
	char	*line_cursor;

	line_cursor = ft_trimr(line);
	line_cursor = ft_strchr(line_cursor, ' ');
	if (!line_cursor)
		return (0);
	line_cursor = ft_strskip_space(line_cursor);
	if (!ft_isdigit(*line_cursor) || *line_cursor == '-')
		return (0);
	settings->cam_sensitivity = (double)ft_atoi(line_cursor);
	if (settings->cam_sensitivity <= 0)
		return (0);
	line_cursor = ft_strskip_digit(line_cursor);
	if (*line_cursor != '.')
		return (0);
	line_cursor++;
	if (!ft_isdigit(*line_cursor))
		return (0);
	settings->cam_sensitivity += ((double)ft_atoi(line_cursor)) / 100.0;
	line_cursor = ft_strskip_digit(line_cursor);
	if (ft_strlen(ft_strskip_space(line_cursor)) > 0)
		return (0);
	if (settings->cam_sensitivity <= 0.5)
		return (0);
	return (1);
}

int	parse_last_save(char *line, t_settings *settings)
{
	char	*line_cursor;

	line_cursor = ft_trimr(line);
	line_cursor = ft_strchr(line_cursor, ' ');
	if (!line_cursor)
		return (0);
	line_cursor = ft_strskip_space(line_cursor);
	if (!*line_cursor)
		return (0);
	settings->last_save = gc_strdup(line_cursor);
	return (1);
}
