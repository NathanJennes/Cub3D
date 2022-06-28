/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_deserialization_mandatory_light.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyril <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:45:01 by njennes           #+#    #+#             */
/*   Updated: 2022/06/29 00:42:48 by Cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"
#include "leaky.h"
#include "map_error.h"

t_bool			is_color_value_legal(char *line);
static t_bool	is_pos_value_legal(char *line, int type);
static int		parse_light_color(t_rgb *color, t_map_parser *parser,
					char **line);
static int		parse_light_pos(t_vec3 *pos, t_map_parser *parser, char *line);

int	parse_light(t_gamestate *gamestate, t_map_parser *parser, char *line)
{
	t_vec3	pos;
	t_rgb	color;

	if (!parse_light_color(&color, parser, &line))
		return (0);
	if (!parse_light_pos(&pos, parser, ft_strskip_space(line + 1)))
		return (0);
	add_light(gamestate, pos, color, DEFAULT_INTENSITY);
	return (1);
}

static int	parse_light_color(t_rgb *color, t_map_parser *parser, char **line)
{
	if (!ft_isdigit(**line))
		return (map_error(*line, parser, MERR_COLOR_EXPECTED_R));
	if (!is_color_value_legal(*line))
		return (map_error(*line, parser, MERR_COLOR_WRONG_VALUE));
	color->r = ft_atoi(*line);
	*line = ft_strskip_digit(*line);
	if (**line != ',')
		return (map_error(*line, parser, MERR_COLOR_EXPECTED_COMMA));
	if (!ft_isdigit(*(++*line)))
		return (map_error(*line, parser, MERR_COLOR_EXPECTED_G));
	if (!is_color_value_legal(*line))
		return (map_error(*line, parser, MERR_COLOR_WRONG_VALUE));
	color->g = ft_atoi(*line);
	*line = ft_strskip_digit(*line);
	if (**line != ',')
		return (map_error(*line, parser, MERR_COLOR_EXPECTED_COMMA));
	if (!ft_isdigit(*(++*line)))
		return (map_error(*line, parser, MERR_COLOR_EXPECTED_B));
	if (!is_color_value_legal(*line))
		return (map_error(*line, parser, MERR_COLOR_WRONG_VALUE));
	color->b = ft_atoi(*line);
	*line = ft_strskip_digit(*line);
	return (1);
}

static int	parse_light_pos(t_vec3 *pos, t_map_parser *parser, char *line)
{
	if (!ft_isdigit(*line))
		return (map_error(line, parser, MERR_POS_EXPECTED));
	if (!is_pos_value_legal(line, X_POS))
		return (map_error(line, parser, MERR_POS_OUTBOUND));
	pos->x = ft_atoi(line);
	line = ft_strskip_digit(line);
	if (*line != ',')
		return (map_error(line, parser, MERR_COLOR_EXPECTED_COMMA));
	if (!ft_isdigit(*(++line)))
		return (map_error(line, parser, MERR_POS_EXPECTED));
	if (!is_pos_value_legal(line, Y_POS))
		return (map_error(line, parser, MERR_POS_OUTBOUND));
	pos->y = ft_atoi(line);
	line = ft_strskip_digit(line);
	if (*line != ',')
		return (map_error(line, parser, MERR_COLOR_EXPECTED_COMMA));
	if (!ft_isdigit(*(++line)))
		return (map_error(line, parser, MERR_POS_EXPECTED));
	if (!is_pos_value_legal(line, Z_POS))
		return (map_error(line, parser, MERR_POS_OUTBOUND));
	pos->z = ft_atoi(line);
	return (1);
}

// TODO: segfault
static t_bool	is_pos_value_legal(char *line, int type)
{
	double		val;
	t_map_info	*map;

	// TODO Need to get the right height and width
	map = get_map_infos();
	val = ft_atoi(line);
	if (type == X_POS && (val < 0 || val >= map->width * CELL_SIZE))
		return (FALSE);
	else if (type == Y_POS && (val < 0 || val >= map->height * CELL_SIZE))
		return (FALSE);
	else if (type == Z_POS && (val < 0 || val >= CELL_SIZE))
		return (FALSE);
	return (TRUE);
}
