/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:17:43 by njennes           #+#    #+#             */
/*   Updated: 2022/06/29 14:11:41 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ERROR_H
# define MAP_ERROR_H

# include <stdint.h>
# include "libft.h"

typedef struct s_map_parser	t_map_parser;
typedef struct s_map_info	t_map_info;

# define MERR_UNRECOGNIZED_LINE "Unrecognized line"

# define MERR_POS_EXPECTED "Expected a positive position value. Syntax: X,Y,Z (> 0)"
# define MERR_LIGHT_POS_OUTBOUND "Invalid light position given. Outside of map bound"

# define MERR_COLOR_EXPECTED_R "Expected a positive red color value. Syntax: R,G,B (0-255)"
# define MERR_COLOR_EXPECTED_B "Expected a positive blue color value. Syntax: R,G,B (0-255)"
# define MERR_COLOR_EXPECTED_G "Expected a positive green color value. Syntax: R,G,B (0-255)"
# define MERR_COLOR_EXPECTED_COMMA "Expected a comma"
# define MERR_COLOR_WRONG_VALUE "Invalid value given to a color channel. They should be between 0 and 255"

# define MERR_TEXTURE_EXPECTED_NAME "Expected a texture name"
# define MERR_TEXTURE_WRONG_FILE "Couldn't load the texture"
# define MERR_TEXTURE_REDEFINITION "A texture for this side was already defined"

# define MERR_MAP_EMPTY "No map_menu layout was given in the file"
# define MERR_MAP_SIZE "Invalid map_menu size: this map_menu doesn't allow any valid spawn position"
# define MERR_MAP_REDEFINITION "The map_menu layout cannot be split into multiple part in the map_menu file"
# define MERR_MAP_WRONG_CHAR "Invalid character in the map_menu layout definition"
# define MERR_MAP_INVALID_LINE_SIDES "Invalid line: the map_menu layout contains tiles that are not closed by walls"
# define MERR_MAP_HOLE_NORTH "This tile should have a wall above it"
# define MERR_MAP_HOLE_SOUTH "This tile should have a wall below it"
# define MERR_MAP_EDGE_NOT_WALL "Invalid tile: there may only be walls surrounding the map_menu"
# define MERR_MAP_SPAWN_REDEFINITION "A map_menu cannot contain more than one spawn"
# define MERR_MAP_NO_SPAWN "A map_menu needs to contain a spawn point"

int	map_error(char *line, t_map_parser *parser, const char *error);
int	map_error_layout(t_map_info *infos, t_map_parser *parser, const char *error,
		t_ivec2 pos);
int	map_print_error(t_map_parser *parser);
int	map_print_error_layout(t_map_parser *parser);

#endif
