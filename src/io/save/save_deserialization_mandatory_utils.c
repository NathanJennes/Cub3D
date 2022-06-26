/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_deserialization_mandatory_utils.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:45:01 by njennes           #+#    #+#             */
/*   Updated: 2022/06/23 14:10:47 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"
#include "map_error.h"

t_bool	is_color_value_legal(char *line);

int	parse_color(t_rgb *color, t_map_parser *parser, char *line)
{
	if (!ft_isdigit(*line))
		return (map_error(line, parser, MERR_COLOR_EXPECTED_R));
	if (!is_color_value_legal(line))
		return (map_error(line, parser, MERR_COLOR_WRONG_VALUE));
	color->r = ft_atoi(line);
	line = ft_strskip_digit(line);
	if (*line != ',')
		return (map_error(line, parser, MERR_COLOR_EXPECTED_COMMA));
	if (!ft_isdigit(*(++line)))
		return (map_error(line, parser, MERR_COLOR_EXPECTED_G));
	if (!is_color_value_legal(line))
		return (map_error(line, parser, MERR_COLOR_WRONG_VALUE));
	color->g = ft_atoi(line);
	line = ft_strskip_digit(line);
	if (*line != ',')
		return (map_error(line, parser, MERR_COLOR_EXPECTED_COMMA));
	if (!ft_isdigit(*(++line)))
		return (map_error(line, parser, MERR_COLOR_EXPECTED_B));
	if (!is_color_value_legal(line))
		return (map_error(line, parser, MERR_COLOR_WRONG_VALUE));
	color->b = ft_atoi(line);
	return (1);
}

int	parse_texture(t_map_info *info, t_map_parser *parser, char *line, int direction)
{
	if (info->tx_list[direction] != INVALID_TEXTURE)
		return (map_error(line, parser, MERR_TEXTURE_REDEFINITION));
	if (!*line)
		return (map_error(line, parser, MERR_TEXTURE_EXPECTED_NAME));
	info->tx_list[direction] = load_texture(line);
	if (info->tx_list[direction] == INVALID_TEXTURE)
		return (map_error(line, parser, MERR_TEXTURE_WRONG_FILE));
	return (1);
}

int	add_map_row(t_map_info *infos, t_map_parser *parser, char *line)
{
	if (parser->map_line_offset == -1)
		parser->map_line_offset = parser->line_number;
	infos->height++;
	line = ft_trimr(line);
	if (!infos->map_raw)
		infos->map_raw = gc_strarray_init();
	infos->map_raw = gc_strarray_append(infos->map_raw, line);
	if ((int64_t)ft_strlen(line) > infos->width)
		infos->width = (int64_t)ft_strlen(line);
	infos->screen_height = infos->height * CELL_SIZE;
	infos->screen_width = infos->width * CELL_SIZE;
	return (1);
}

t_bool	is_color_value_legal(char *line)
{
	size_t	i;

	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	if (i == 0 || i > 3)
		return (FALSE);
	return (TRUE);
}
