/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saves_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 14:57:26 by njennes           #+#    #+#             */
/*   Updated: 2022/06/15 14:35:59 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "core.h"
#include "leaky.h"

static void	add_to_saves(char *save_name);
static void	grow_saves_array(void);

void	load_all_saves(void)
{
	DIR				*dir;
	struct dirent	*curr_dir;

	dir = opendir(APPDATA_DIRECTORY);
	if (dir == NULL)
		return ;
	curr_dir = readdir(dir);
	while (curr_dir != NULL)
	{
		if (curr_dir->d_type == DT_REG && ft_strcmp(curr_dir->d_name, ".") != 0
			&& ft_strcmp(curr_dir->d_name, "..") != 0
			&& ft_end_with(curr_dir->d_name, ".save"))
			add_to_saves(curr_dir->d_name);
		curr_dir = readdir(dir);
	}
	closedir(dir);
}

void	reload_saves(void)
{
	unload_saves();
	load_all_saves();
}

void	unload_saves(void)
{
	t_mlx	*app;
	size_t	i;

	app = get_app();
	i = 0;
	while (i < app->savegames_count)
	{
		free_save(&app->savegames[i]);
		i++;
	}
	gc_free(app->savegames);
}

static void	add_to_saves(char *save_name)
{
	t_mlx		*app;
	t_gamestate	save;

	if (!load_game(&save, save_name))
		return ;
	grow_saves_array();
	app = get_app();
	app->savegames[app->savegames_count] = save;
	app->savegames_count++;
}

static void	grow_saves_array(void)
{
	t_mlx		*app;
	t_gamestate	*new;

	app = get_app();
	new = gc_calloc(app->savegames_count + 1, sizeof (t_gamestate));
	if (app->savegames)
	{
		ft_memmove(new, app->savegames,
			app->savegames_count * sizeof (t_gamestate));
		gc_free(app->savegames);
	}
	app->savegames = new;
}
