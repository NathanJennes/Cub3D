/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loaded_map_manager.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:58:37 by njennes           #+#    #+#             */
/*   Updated: 2022/06/15 14:35:59 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "core.h"
#include "leaky.h"

static void	add_to_maps(char *save_name);
static void	grow_maps_array(void);

void	load_all_maps(void)
{
	DIR				*dir;
	struct dirent	*curr_dir;

	dir = opendir(MAPS_DIRECTORY);
	if (dir == NULL)
		return ;
	curr_dir = readdir(dir);
	while (curr_dir != NULL)
	{
		if (curr_dir->d_type == DT_REG && ft_strcmp(curr_dir->d_name, ".") != 0
			&& ft_strcmp(curr_dir->d_name, "..") != 0
			&& ft_end_with(curr_dir->d_name, ".cub"))
			add_to_maps(curr_dir->d_name);
		curr_dir = readdir(dir);
	}
	closedir(dir);
}

void	reload_maps(void)
{
	unload_maps();
	load_all_maps();
	refresh_new_game_menu();
}

void	unload_maps(void)
{
	t_mlx	*app;
	int64_t	i;

	app = get_app();
	i = 0;
	while (i < app->maps_count)
	{
		free_save(&app->maps[i]);
		i++;
	}
	gc_free(app->maps);
}

static void	add_to_maps(char *save_name)
{
	t_mlx		*app;
	t_gamestate	save;

	if (!load_map(&save, save_name))
		return ;
	grow_maps_array();
	app = get_app();
	app->maps[app->maps_count] = save;
	app->maps_count++;
}

static void	grow_maps_array(void)
{
	t_mlx		*app;
	t_gamestate	*new;

	app = get_app();
	new = gc_calloc(app->maps_count + 1, sizeof (t_gamestate));
	if (app->maps)
	{
		ft_memmove(new, app->maps,
			app->maps_count * sizeof (t_gamestate));
		gc_free(app->maps);
	}
	app->maps = new;
}
