/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_listeners.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:42:50 by njennes           #+#    #+#             */
/*   Updated: 2022/06/26 17:37:20 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"
#include "input_code.h"
#include "leaky.h"

inline static void	handle_escape(void);
inline static void	turn_off_lights(void);
inline static void	turn_on_lights(void);

int	key_pressed_listener(int keycode)
{
	t_mlx	*app;

	app = get_app();
	if (keycode == KEY_BACKSPACE)
		close_app();
	else if (keycode == KEY_F3)
		switch_debug_ui();
	else if (keycode == KEY_TAB)
	{
		app->ui.lock_crosshair = !app->ui.lock_crosshair;
		if (app->ui.lock_crosshair == TRUE)
		{
			mlx_mouse_hide();
			reset_mouse_pos();
		}
		else
			mlx_mouse_show();
	}
	else if (keycode == KEY_ESC)
		handle_escape();
	else if (keycode == KEY_F4)
		app->renderer.multithreading = !app->renderer.multithreading;
	else if (keycode == KEY_F10)
		app->mandatory = !app->mandatory;
	else if (keycode == KEY_E && app->state == IN_GAME)
		turn_off_lights();
	else if (keycode == KEY_Q && app->state == IN_GAME)
		turn_on_lights();
	return (0);
}

inline static void	handle_escape(void)
{
	t_mlx	*app;
	char	*save_name;

	app = get_app();
	mlx_mouse_show();
	if (app->state == IN_GAME)
	{
		save_name = save_game(app->gamestate.name);
		if (save_name)
		{
			gc_free(app->settings.last_save);
			app->settings.last_save = gc_strdup(save_name);
		}
		else
			printf("Can't save save\n");
		refresh_main_menu();
		app->state = IN_MENU;
		app->ui.state = MAIN_MENU;
		mlx_mouse_show();
	}
	else if (app->state == IN_MENU)
	{
		if (app->ui.state == NEW_GAME_MENU)
			app->ui.state = MAIN_MENU;
		else if (app->ui.state == LOAD_MENU)
			app->ui.state = MAIN_MENU;
		else if (app->ui.state == OPTION_MENU)
			app->ui.state = MAIN_MENU;
		else if (app->ui.state == MAIN_MENU)
			close_app();
	}
}

inline static void	turn_off_lights(void)
{
	int64_t		i;
	t_gamestate	*game;

	game = &get_app()->gamestate;
	i = 0;
	while (i < game->light_count)
	{
		if (ft_pow2(game->lights[i].pos.x - game->player.world_pos.x) +
			ft_pow2(game->lights[i].pos.y - game->player.world_pos.y) < CELL_SIZE * CELL_SIZE)
			game->lights[i].enabled = FALSE;
		i++;
	}
}

inline static void	turn_on_lights(void)
{
	int64_t		i;
	t_gamestate	*game;

	game = &get_app()->gamestate;
	i = 0;
	while (i < game->light_count)
	{
		if (ft_pow2(game->lights[i].pos.x - game->player.world_pos.x) +
			ft_pow2(game->lights[i].pos.y - game->player.world_pos.y) <
			CELL_SIZE * CELL_SIZE)
			game->lights[i].enabled = TRUE;
		i++;
	}
}

