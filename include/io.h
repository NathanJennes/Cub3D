/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:45:17 by njennes           #+#    #+#             */
/*   Updated: 2022/05/16 18:35:40 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# define APPDATA_DIRECTORY "appdata"

typedef struct s_gamestate	t_gamestate;

int			save_game(char *save_name);
int			load_game(t_gamestate *save_out, char *save_name);
void		free_save(t_gamestate *save);

void		load_all_saves(void);
void		unload_saves(void);
void		reload_saves(void);

#endif
