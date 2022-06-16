/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:30:18 by njennes           #+#    #+#             */
/*   Updated: 2022/06/16 16:32:08 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_error.h"
#include "io.h"
#include "libft.h"

int	map_error(char *line, t_map_parser *parser, const char *error)
{
	parser->error_message = error;
	parser->column = ft_strlen(parser->line) - ft_strlen(line);
	return (0);
}
