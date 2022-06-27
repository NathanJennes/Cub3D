/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_listeners.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:42:50 by njennes           #+#    #+#             */
/*   Updated: 2022/06/27 14:52:14 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"
#include "input_code.h"
#include "leaky.h"

void			handle_f1(t_mlx *app);
inline static void	handle_escape(void);
inline static void	handle_tab(t_mlx *app);
inline static void	turn_off_lights(void);
inline static void	turn_on_lights(void);

int	key_pressed_listener(int keycode)
{
	t_mlx	*app;

	app = get_app();
	if (keycode == KEY_BACKSPACE)
		close_app();
	else if (keycode == KEY_TAB)
		handle_tab(app);
	else if (keycode == KEY_ESC)
		handle_escape();
	else if (keycode == KEY_F1)
		handle_f1(app);
	else if (keycode == KEY_F2)
		app->mandatory = !app->mandatory;
	else if (keycode == KEY_F3)
		handle_debug_ui();
	else if (keycode == KEY_F4)
		app->renderer.multithreading = !app->renderer.multithreading;
	else if (keycode == KEY_E && app->state == IN_GAME)
		turn_off_lights();
	else if (keycode == KEY_Q && app->state == IN_GAME)
		turn_on_lights();
	return (0);
}

inline static void	handle_tab(t_mlx *app)
{
	if (app->state != IN_GAME)
		return ;
	if (app->ui.state == MAP_MENU)
	{
		app->gamestate.player.lock = FALSE;
		app->ui.state = NONE;
		app->editor_mode = FALSE;
		app->ui.map_menu.chk_editor_mode.checked = FALSE;
		mlx_mouse_hide();
		reset_mouse_pos();
		return ;
	}
	app->gamestate.player.lock = TRUE;
	app->ui.state = MAP_MENU;
	mlx_mouse_show();
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
		return ;
	}
	if (app->ui.state != MAIN_MENU)
		app->ui.state = MAIN_MENU;
	else if (app->ui.state == MAIN_MENU)
		close_app();
}

inline static void	turn_off_lights(void)
{
	int64_t		i;
	t_gamestate	*game;

	game = &get_app()->gamestate;
	i = 0;
	while (i < game->light_count)
	{
		if (ft_pow2(game->lights[i].pos.x - game->player.world_pos.x) + \
			ft_pow2(game->lights[i].pos.y - game->player.world_pos.y) < \
			CELL_SIZE * CELL_SIZE)
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
		if (ft_pow2(game->lights[i].pos.x - game->player.world_pos.x) + \
			ft_pow2(game->lights[i].pos.y - game->player.world_pos.y) < \
			CELL_SIZE * CELL_SIZE)
			game->lights[i].enabled = TRUE;
		i++;
	}
}
