/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_deserialization_mandatory.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:26:19 by njennes           #+#    #+#             */
/*   Updated: 2022/05/26 15:18:06 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaky.h"
#include "core.h"

void		construct_map(t_map_info *infos)NOPROF;
int			parse_color(t_vec3 *color, char *line)NOPROF;
int			parse_texture(char **path, char *line)NOPROF;
int			add_map_row(t_map_info *infos, char *line)NOPROF;

static int	parse_line(t_map_info *infos, char *line)NOPROF;
static void	setup_player(t_gamestate *save)NOPROF;

int	load_mandatory_map(t_gamestate *save_out, int fd, char *line)
{
	t_map_info	*infos;

	ft_memset(save_out, 0, sizeof (t_gamestate));
	infos = &save_out->map;
	while (line)
	{
		parse_line(infos, line);
		gc_free(line);
		line = gc_get_next_line(fd);
	}
	if (!infos->map_raw)
		return (0);
	construct_map(infos);
	if (!infos->spawn_dir)
		return (0);
	gc_strarray_free(infos->map_raw);
	setup_player(save_out);
	return (1);
}

static int	parse_line(t_map_info *infos, char *line)
{
	if (line[0] == '\n')
		return (1);
	if (ft_isdigit(line[0]) || line[0] == ' ')
		return (add_map_row(infos, line));
	else if (infos->map)
		return (0);
	if (line[0] == 'C' && line[1] == ' ')
		return (parse_color(&infos->ceiling_color,
				ft_strskip_space(line + 1)));
	else if (line[0] == 'F' && line[1] == ' ')
		return (parse_color(&infos->floor_color, ft_strskip_space(line + 1)));
	else if (ft_strcmp(line, "NO") == 0 && line[3] == ' ')
		return (parse_texture(&infos->no_tex, ft_strskip_space(line + 3)));
	else if (ft_strcmp(line, "SO") == 0 && line[3] == ' ')
		return (parse_texture(&infos->so_tex, ft_strskip_space(line + 3)));
	else if (ft_strcmp(line, "EA") == 0 && line[3] == ' ')
		return (parse_texture(&infos->ea_tex, ft_strskip_space(line + 3)));
	else if (ft_strcmp(line, "WE") == 0 && line[3] == ' ')
		return (parse_texture(&infos->we_tex, ft_strskip_space(line + 3)));
	return (0);
}

static void	setup_player(t_gamestate *save)
{
	if (save->map.spawn_dir == 'N')
		save->player.direction = PI;
	else if (save->map.spawn_dir == 'E')
		save->player.direction = PI / 2.0;
	else if (save->map.spawn_dir == 'S')
		save->player.direction = 0.0;
	else if (save->map.spawn_dir == 'W')
		save->player.direction = PI * 3.0 / 2.0;
	save->player.world_pos = save->map.spawn_pos;
	update_player(&save->player);
}
