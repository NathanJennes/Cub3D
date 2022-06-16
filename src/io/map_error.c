/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:30:18 by njennes           #+#    #+#             */
/*   Updated: 2022/06/16 20:08:27 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_error.h"
#include "io.h"
#include "libft.h"
#include "core.h"
#include "leaky.h"

int	map_error(char *line, t_map_parser *parser, const char *error)
{
	parser->error_message = error;
	parser->column = ft_strlen(parser->line) - ft_strlen(line);
	parser->error_line_number = parser->line_number;
	parser->error_layout = FALSE;
	parser->error_layout_global = FALSE;
	return (0);
}

int	map_error_layout(t_map_info *infos, t_map_parser *parser, const char *error, t_ivec2 pos)
{
	parser->error_message = error;
	parser->column = ft_strlen(infos->map_raw[pos.y]) - ft_strlen(infos->map_raw[pos.y] + pos.x);
	parser->error_line_number = parser->map_line_offset + pos.y;
	parser->infos = infos;
	parser->error_layout = TRUE;
	parser->line = infos->map_raw[pos.y];
	if (pos.x == -1 || pos.y == -1)
		parser->error_layout_global = TRUE;
	else
		parser->error_layout_global = FALSE;
	return (0);
}

int	map_print_error(t_map_parser *parser)
{
	size_t	i;

	if (parser->error_layout)
		return (map_print_error_layout(parser));
	printf("Error while loading: %s\n", parser->filename);
	if (parser->line)
	{
		printf("Line %lld: %s\n", parser->error_line_number + 1, parser->line);
		i = 0;
		while (i < parser->column + 5 + ft_nbrlen(parser->error_line_number))
		{
			printf(" ");
			i++;
		}
		printf("~~^~~\n");
	}
	printf("%s\n", parser->error_message);
	gc_free(parser->line);
	return (0);
}

int	map_print_error_layout(t_map_parser *parser)
{
	t_ivec2	it;

	printf("Error while loading: %s\n", parser->filename);
	printf("Line %lld: %s\n", parser->error_line_number, parser->line);
	it = ivec2_zero();
	while (it.y < parser->infos->height)
	{
		printf("  %s\n", parser->infos->map_raw[it.y]);
		if (it.y + parser->map_line_offset == parser->error_line_number && !parser->error_layout_global)
		{
			it.x = 0;
			while (it.x < (int64_t)parser->column)
			{
				printf(" ");
				it.x++;
			}
			printf("~~^~~\n");
			printf("%s\n", parser->error_message);
		}
		it.y++;
	}
	return (0);
}
