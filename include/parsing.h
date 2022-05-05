/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:32:54 by njennes           #+#    #+#             */
/*   Updated: 2022/05/05 15:37:04 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "core.h"

void	init_map(char *file);

t_vec3	parse_color(char *line);
char	*parse_texture(char *line);
void	add_map_row(t_map_info *infos, char *line);

#endif