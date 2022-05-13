/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:00:13 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/13 17:20:16 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"

int	ui_manager(void)
{
	t_mlx			*app;
	t_ui			*ui;

	app = get_app();
	ui = get_ui();
	/* HUD */
	if (app->game_state == IN_GAME)
	{
		render_mmap(ui->map_scale_slider.value);
		show_slider(&ui->map_scale_slider);
		mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	}
	/* Menu */
	if (app->game_state == MENU)
	{
		if (ui->flags & MAIN_MENU)
		{
			put_xpm_to_window("assets/ui/select_bar.xpm", ui->select_bar_pos);
			put_xpm_to_window("assets/ui/main_menu.xpm", vec2(0, 0));
		}
		if (ui->flags & OPTION_MENU)
		{
			put_xpm_to_window("assets/ui/select_bar.xpm", ui->select_bar_pos);
			put_xpm_to_window("assets/ui/option_menu.xpm", vec2(0, 0));
		}
	}
	/* Debug */
	if (app->ui.flags & DEBUG_UI)
		fps_counter();
	return (0);
}

void	update_ui_flags(uint8_t flag)
{
	t_mlx	*app;

	app = get_app();
	if (app->ui.flags & flag)
		app->ui.flags ^= flag;
	else
		app->ui.flags |= flag;
}
