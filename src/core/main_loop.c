/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:44:35 by njennes           #+#    #+#             */
/*   Updated: 2022/05/09 17:06:57 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"
#include "render.h"

int	main_loop()
{
	t_mlx	*app;

	app = get_app();
	clear_screen(BKGD_COLOR);
	render_mmap(app->map_scale_slider.value);
	show_slider(&app->map_scale_slider);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	if (app->ui_flags & DEBUG_UI)
		fps_counter();
	return (0);
}
