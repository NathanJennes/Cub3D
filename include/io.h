/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:45:17 by njennes           #+#    #+#             */
/*   Updated: 2022/05/31 12:58:40 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# define APPDATA_DIRECTORY "appdata"
# define MAPS_DIRECTORY "maps"

typedef struct s_gamestate	t_gamestate;
typedef struct s_settings	t_settings;

int			save_game(char *save_name);
int			load_game(t_gamestate *save_out, char *save_name);
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
