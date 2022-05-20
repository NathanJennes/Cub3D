/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:44:35 by njennes           #+#    #+#             */
/*   Updated: 2022/05/19 19:22:03 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"
#include "render.h"

int	main_loop(void)
{
	t_mlx	*app;

	app = get_app();
	if (app->game_state & IN_GAME){}
		// game frame
	clear_screen(BKGD_COLOR);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	update_ui();
	render_ui();
	return (0);
}
