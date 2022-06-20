/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialization_settings.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyril <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:30:37 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/14 10:27:39 by Cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"

int			parse_fov(char *line, t_settings *settings);
int			parse_sens(char *line, t_settings *settings);

inline static void	set_settings_out(t_settings *settings_out);
inline static int	parse_line_settings(char *line, t_settings *settings);
inline static int	parse_win(char *line, t_settings *settings);

int	deserialize_settings(t_settings *settings_out, int fd)
{
	char	*line;
	int		line_num;

	line = gc_get_next_line(fd);
	line_num = 0;
	while (line)
	{
		line = ft_trimr(line);
		if (!parse_line_settings(line, settings_out))
		{
			gc_free(line);
			printf("Settings file currupted at line: %d\n", line_num);
			return (0);
		}
		gc_free(line);
		line = gc_get_next_line(fd);
		line_num++;
	}
	if (line_num != 3)
	{
		printf("Settings file currupted at line: %d\n", line_num);
		return (0);
	}
	set_settings_out(settings_out);
	return (1);
}

inline static void	set_settings_out(t_settings *settings_out)
{
	settings_out->desired_win_w = settings_out->win_w;
	settings_out->desired_win_h = settings_out->win_h;
	settings_out->halfw_w = settings_out->win_w / 2;
	settings_out->halfw_h = settings_out->win_h / 2;
}

inline static int	parse_line_settings(char *line, t_settings *settings)
{
	if (ft_strncmp(line, "FOV", ft_strlen("FOV")) == 0)
		return (parse_fov(line, settings));
	else if (ft_strncmp(line, "WIN", ft_strlen("WIN")) == 0)
		return (parse_win(line, settings));
	else if (ft_strncmp(line, "SENS", ft_strlen("SENS")) == 0)
		return (parse_sens(line, settings));
	return (0);
}

inline static int	parse_win(char *line, t_settings *settings)
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
