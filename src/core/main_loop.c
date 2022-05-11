/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:44:35 by njennes           #+#    #+#             */
/*   Updated: 2022/05/11 18:47:36 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"
#include "render.h"

int	main_loop(void)
{
	t_mlx	*app;

	app = get_app();
	get_mouse_pos(app);
	clear_screen(BKGD_COLOR);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	if (app->ui.ui_flags == 0)
		ui_main_menu();
	else
	{
		render_mmap(app->map_scale_slider.value);
		show_slider(&app->map_scale_slider);
		mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	}
	if (app->ui.ui_flags & DEBUG_UI)
		fps_counter();
	return (0);
}
