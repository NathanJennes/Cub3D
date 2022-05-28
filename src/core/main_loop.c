/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:44:35 by njennes           #+#    #+#             */
/*   Updated: 2022/05/28 18:23:05 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"
#include "render.h"

void	render_test_scene(const t_mlx *app);
void	debug_print_texture(void);

int	main_loop(void)
{
	t_mlx	*app;

	app = get_app();
	update_player(&app->gamestate.player);
	if (app->game_state & IN_GAME)
	{
		draw_rect_unsafe(ivec2(0, 0), ivec2(WIN_W, HALFW_H), CEILLING);
		draw_rect_unsafe(ivec2(0, HALFW_H), ivec2(WIN_W, HALFW_H), FLOOR);
		render_walls();
		render_test_scene(app);
//		debug_print_texture();
	}
	else
	{
		clear_screen(BKGD_COLOR);
		mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	}
	if (app->ui.debug_ui == TRUE)
		print_debug();
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	update_ui();
	render_ui();
	return (0);
}

void	debug_print_texture(void)
{
	int			i;
	int			j;
	t_texture	*tx;

	i = 0;
	tx = get_texture_from_id(13);
	while (i < tx->height / 2)
	{
		j = 0;
		while (j < tx->width / 2)
		{
			set_screen_pixel(i, j, *(int *)(tx->original + (i * tx->line_size * 2) + (j * 4 * 2)));
			j++;
		}
		i++;
	}
}
