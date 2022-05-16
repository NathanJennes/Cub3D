/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:45:17 by njennes           #+#    #+#             */
/*   Updated: 2022/05/16 15:18:46 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# define APPDATA_DIRECTORY "appdata"

typedef struct s_gamestate	t_gamestate;

void		save_game(char *save_name);
t_gamestate	load_game(char *save_name);
void		free_save(t_gamestate *save);

void		load_all_saves(void);
void		unload_saves(void);
void		reload_saves(void);

#endif
