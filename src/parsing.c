/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:26:19 by njennes           #+#    #+#             */
/*   Updated: 2022/05/05 13:20:28 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "parsing.h"
#include "leaky.h"

static void	parse_line(t_mlx *app, t_map_info *infos, char *line);
static char	*skip_spaces(char *str);
static void	construct_map(t_map_info *infos);

void	init_map(t_mlx *app, char *file)
{
	t_map_info	infos;
	int			fd;
	char		*line;

	ft_memset(&infos, 0, sizeof (t_map_info));
	fd = open(file, O_RDONLY);
	if (!fd || fd == -1)
		error_close_app(app);
	line = gc_get_next_line(fd);
	while (line)
	{
		parse_line(app, &infos, line);
		gc_free(line);
		line = gc_get_next_line(fd);
	}
	if (!infos.map_raw)
		error_close_app(app);
	construct_map(&infos);
	if (!infos.spawn_dir)
		error_close_app(app);
	gc_strarray_free(infos.map_raw);
	app->map = infos;
	app->player.pos = infos.spawn_pos;
}

static void	parse_line(t_mlx *app, t_map_info *infos, char *line)
{
	if (line[0] == '\n')
		return ;
	if (ft_isdigit(line[0]) || line[0] == ' ')
		add_map_row(app, infos, line);
	else if (infos->map)
		error_close_app(app);
	if (line[0] == 'C' && line[1] == ' ')
		infos->ceiling_color = parse_color(app, skip_spaces(line + 1));
	else if (line[0] == 'F' && line[1] == ' ')
		infos->floor_color = parse_color(app, skip_spaces(line + 1));
	else if (ft_strcmp(line, "NO") == 0 && line[3] == ' ')
		infos->no_tex = parse_texture(app, skip_spaces(line + 3));
	else if (ft_strcmp(line, "SO") == 0 && line[3] == ' ')
		infos->so_tex = parse_texture(app, skip_spaces(line + 3));
	else if (ft_strcmp(line, "EA") == 0 && line[3] == ' ')
		infos->ea_tex = parse_texture(app, skip_spaces(line + 3));
	else if (ft_strcmp(line, "WE") == 0 && line[3] == ' ')
		infos->we_tex = parse_texture(app, skip_spaces(line + 3));
}

static char	*skip_spaces(char *str)
{
	while (*str == ' ')
		str++;
	return (str);
}

static void	construct_map(t_map_info *infos)
{
	size_t	i;
	size_t	j;
	int		*row;

	infos->map = gc_calloc(infos->height, sizeof (int *));
	i = 0;
	while (i < infos->height)
	{
		row = gc_calloc(infos->width, sizeof (int));
		j = 0;
		while (j < infos->width)
		{
			if (infos->map_raw[i][j] == ' ')
				row[j] = VOID;
			else if (infos->map_raw[i][j] == '1')
				row[j] = WALL;
			else
				row[j] = EMPTY;
			if (ft_isalpha(infos->map_raw[i][j]))
			{
				infos->spawn_dir = infos->map_raw[i][j];
				infos->spawn_pos = (t_vec2){j, i};
			}
			j++;
		}
		infos->map[i] = row;
		i++;
	}
}
