/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:43:54 by njennes           #+#    #+#             */
/*   Updated: 2022/05/15 16:12:10 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "parsing.h"

static void	init_hooks(void);
static void	init_ui(void);

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
	init_ui();
	load_all_saves();
	printf("loaded: %d\n", (int)app->savegames_count);
	if (app->savegames_count == 0)
		init_map(file);
	else
		app->gamestate = app->savegames[0];
	init_window("Cub3d");
	init_hooks();
	mlx_loop(get_mlx());
}

static void	init_hooks(void)
{
	t_mlx	*app;

	app = get_app();
	mlx_mouse_hook(app->win, mouse_hooks, app);
	mlx_hook(app->win, 17, 0, close_app, app);
	mlx_hook(app->win, 2, 1L << 0, key_hooks, app);
	mlx_loop_hook(app->mlx, main_loop, app);
}

static void	init_ui(void)
{
	t_mlx	*app;

	app = get_app();
	app->map_scale_slider.pos = vec2(WIN_W - 150, 10);
	app->map_scale_slider.increment_size = 0.1f;
	app->map_scale_slider.value = 1.0f;
	app->map_scale_slider.min = 0.2f;
	app->map_scale_slider.max = 5.0f;
	app->map_scale_slider.displayed = 1;
}
