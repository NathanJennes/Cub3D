/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:44:35 by njennes           #+#    #+#             */
/*   Updated: 2022/05/20 11:20:55 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"

void	render_test_scene(const t_mlx *app);

int	main_loop(void)
{
	t_mlx	*app;

	app = get_app();
	clear_screen(BKGD_COLOR);
	if (app->game_state & IN_GAME)
		render_walls();
	render_test_scene(app);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	if (app->ui.debug_ui == TRUE)
		print_debug();
	return (0);
}
