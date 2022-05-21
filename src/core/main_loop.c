/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:44:35 by njennes           #+#    #+#             */
/*   Updated: 2022/05/21 20:03:42 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"
#include "render.h"

int	main_loop(void)
{
	t_mlx	*app;

	app = get_app();
	if (app->game_state & IN_GAME)
	{
	}
	clear_screen(BKGD_COLOR);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	render_text("ceci est un text!", "HelveticaNeue", 72, ivec2(10, 10));
	render_text("Ca fonctionne!!!", "HelveticaNeue", 30, ivec2(10, 110));
	render_text("aaaa", "HelveticaNeue", 30, ivec2(10, 150));
	render_text("aa", "HelveticaNeue", 60, ivec2(10, 230));
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	//update_ui();
	//render_ui();
	return (0);
}
