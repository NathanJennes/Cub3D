/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:00:13 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/15 16:25:00 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
# include "render.h"
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
		if (ui->state & MAIN_MENU)
		{
//			render_ui_texture(2, 360, 170);
//			render_ui_texture(0, 0, 0);
		}
		else if (ui->state & OPTION_MENU)
		{
//			render_ui_texture(2, 360, 170);
//			render_ui_texture(1, 0, 0);
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
