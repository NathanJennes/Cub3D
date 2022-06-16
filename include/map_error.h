/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:17:43 by njennes           #+#    #+#             */
/*   Updated: 2022/06/16 17:28:20 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ERROR_H
# define MAP_ERROR_H

typedef struct s_map_parser	t_map_parser;

# define MERR_MAP_REDEFINITION "The map layout cannot be split into multiple part in the map file"
# define MERR_UNRECOGNIZED_LINE "Unrecognized line"

# define MERR_COLOR_EXPECTED_R "Expected a positive red color value. Syntax: R,G,B (0-255)"
# define MERR_COLOR_EXPECTED_B "Expected a positive blue color value. Syntax: R,G,B (0-255)"
# define MERR_COLOR_EXPECTED_G "Expected a positive green color value. Syntax: R,G,B (0-255)"
# define MERR_COLOR_EXPECTED_COMMA "Expected a comma"
# define MERR_COLOR_WRONG_VALUE "Invalid value given to a color channel. They should be between 0 and 255"

# define MERR_TEXTURE_EXPECTED_NAME "Expected a texture name"
# define MERR_TEXTURE_WRONG_FILE "Couldn't load the texture"
# define MERR_TEXTURE_REDEFINITION "A texture for this side was already defined"

int	map_error(char *line, t_map_parser *parser, const char *error);

#endif
