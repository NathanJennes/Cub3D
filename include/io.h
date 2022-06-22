/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:45:17 by njennes           #+#    #+#             */
/*   Updated: 2022/06/16 19:37:41 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include <stdint.h>
# include <stddef.h>
# include "bool.h"

# define APPDATA_DIRECTORY "appdata"
# define MAPS_DIRECTORY "maps"

# define MEMPTY 0
# define MWIP 1
# define MFINISHED 2

typedef struct s_gamestate	t_gamestate;
typedef struct s_settings	t_settings;
typedef struct s_map_info	t_map_info;

typedef struct s_map_parser
{
	int64_t		map_line_offset;
	int64_t		line_number;
	int64_t		error_line_number;
	size_t		column;
	const char	*error_message;
	char		*line;
	char		*filename;
	t_bool		error_layout;
	t_bool		error_layout_global;
	t_map_info	*infos;
}			t_map_parser;

int			save_game(char *save_name);
int			load_save(t_gamestate *save_out, char *save_name);
int			load_map(t_gamestate *map_out, char *map_name);
void		free_save(t_gamestate *save);

void		load_all_saves(void);
void		unload_saves(void);
void		reload_saves(void);

void		load_all_maps(void);
void		unload_maps(void);
void		reload_maps(void);

t_settings	load_settings(void);
void		save_settings(t_settings *settings);

#endif
