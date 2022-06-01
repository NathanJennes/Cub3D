/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialization_settings.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:30:37 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/31 12:58:14 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"

static int	parse_line(char *line, t_settings *settings);
static int	parse_fov(char *line, t_settings *settings);
static int	parse_win(char *line, t_settings *settings);

int	deserialize_settings(t_settings *settings_out, int fd)
{
	char	*line;
	int		line_num;

	line = gc_get_next_line(fd);
	line_num = 0;
	while (line)
	{
		line = ft_trimr(line);
		if (!parse_line(line, settings_out))
		{
			gc_free(line);
			printf("Settings file currupted at line: %d\n", line_num);
			return (0);
		}
		gc_free(line);
		line = gc_get_next_line(fd);
		line_num++;
	}
	if (line_num != 2)
	{
		printf("Settings file currupted at line: %d\n", line_num);
		return (0);
	}
	settings_out->desired_win_w = settings_out->win_w;
	settings_out->desired_win_h = settings_out->win_h;
	return (1);
}

static int	parse_line(char *line, t_settings *settings)
{
	if (ft_strncmp(line, "FOV", ft_strlen("FOV")) == 0)
		return (parse_fov(line, settings));
	if (ft_strncmp(line, "WIN", ft_strlen("WIN")) == 0)
		return (parse_win(line, settings));
	return (0);
}

static int	parse_fov(char *line, t_settings *settings)
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

static int	parse_win(char *line, t_settings *settings)
{
	char	*line_cursor;

	line_cursor = ft_trimr(line);
	line_cursor = ft_strchr(line_cursor, ' ');
	if (!line_cursor)
		return (0);
	line_cursor = ft_strskip_space(line_cursor);
	if (!ft_isdigit(*line_cursor) || *line_cursor == '-')
		return (0);
	settings->win_w = ft_atoi(line_cursor);
	if (settings->win_w <= 0)
		return (0);
	line_cursor = ft_strskip_digit(line_cursor);
	line_cursor = ft_strskip_space(line_cursor);
	if (!ft_isdigit(*line_cursor) || *line_cursor == '-')
		return (0);
	settings->win_h = ft_atoi(line_cursor);
	if (settings->win_h <= 0)
		return (0);
	line_cursor = ft_strskip_digit(line_cursor);
	if (ft_strlen(ft_strskip_space(line_cursor)) > 0)
		return (0);
	return (1);
}
