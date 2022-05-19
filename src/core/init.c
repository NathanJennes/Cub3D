/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:43:54 by njennes           #+#    #+#             */
/*   Updated: 2022/05/15 16:15:08 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "parsing.h"
#include "ui.h"

static void	init_hooks(void);

int	is_legal_file(int argc, char **argv)
{
	char	*extension;

	if (argc != 2)
		return (0);
	extension = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]));
	if (!extension)
		return (0);
	if (extension[4])
		return (0);
	return (1);
}

void	init_app(char *file)
{
	t_mlx	*app;

	app = get_app();
	init_gc();
	init_window("Cub3d");
	init_ui();
	load_all_saves();
	printf("loaded: %d\n", (int)app->savegames_count);
	if (app->savegames_count == 0)
		init_map(file);
	else
		app->gamestate = app->savegames[0];
	init_hooks();
	mlx_loop(get_mlx());
}

static void init_hooks(void)
{
	t_mlx	*app;

	app = get_app();
	app->game_state = IN_GAME;
	mlx_mouse_hook(app->win, mouse_hooks, app);
	mlx_hook(app->win, 6, 1L<<6, mouse_move_hooks, app);
	mlx_hook(app->win, 17, 0, close_app, app);
	mlx_hook(app->win, 2, 1L << 0, key_hooks, app);
	mlx_loop_hook(app->mlx, main_loop, app);
}
