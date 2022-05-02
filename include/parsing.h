/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:32:54 by njennes           #+#    #+#             */
/*   Updated: 2022/05/02 15:46:40 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "core.h"

void	init_map(t_mlx *app, char *file);

t_vec3	parse_color(t_mlx *app, char *line);
char	*parse_texture(t_mlx *app, char *line);
void	add_map_row(t_mlx *app, t_map_info *infos, char *line);

#endif