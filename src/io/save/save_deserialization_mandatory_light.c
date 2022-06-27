/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_deserialization_mandatory_light.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:45:01 by njennes           #+#    #+#             */
/*   Updated: 2022/06/23 19:39:07 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"
#include "leaky.h"
#include "map_error.h"

t_bool			is_color_value_legal(char *line);
static t_bool	is_pos_value_legal(char *line);
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
	if (!is_pos_value_legal(line))
		return (map_error(line, parser, MERR_POS_OUTBOUND));
	pos->x = ft_atoi(line);
	line = ft_strskip_digit(line);
	if (*line != ',')
		return (map_error(line, parser, MERR_COLOR_EXPECTED_COMMA));
	if (!ft_isdigit(*(++line)))
		return (map_error(line, parser, MERR_POS_EXPECTED));
	if (!is_pos_value_legal(line))
		return (map_error(line, parser, MERR_POS_OUTBOUND));
	pos->y = ft_atoi(line);
	line = ft_strskip_digit(line);
	if (*line != ',')
		return (map_error(line, parser, MERR_COLOR_EXPECTED_COMMA));
	if (!ft_isdigit(*(++line)))
		return (map_error(line, parser, MERR_POS_EXPECTED));
	if (!is_pos_value_legal(line))
		return (map_error(line, parser, MERR_POS_OUTBOUND));
	pos->z = ft_atoi(line);
	return (1);
}

// TODO: do good below
static t_bool	is_pos_value_legal(char *line)
{
	size_t	i;

	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	if (i == 0 || i > 4)
		return (FALSE);
	return (TRUE);
}
