/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 14:13:05 by njennes           #+#    #+#             */
/*   Updated: 2022/06/22 17:13:42 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	init_window(char *win_name)
{
	t_mlx		*app;
	t_settings	*settings;

	app = get_app();
	settings = get_settings();
	app->mlx = mlx_init();
	if (!app->mlx)
		error_close_app("Error: couldn't initialize mlx");
	app->win = \
		mlx_new_window(app->mlx, settings->win_w, settings->win_h, win_name);
	if (!app->win)
		error_close_app("Error: couldn't create a window");
	app->frame.img = mlx_new_image(app->mlx, settings->win_w, settings->win_h);
	if (!app->frame.img)
		error_close_app("Error: couldn't create an image");
	app->frame.addr = mlx_get_data_addr(app->frame.img, &app->frame.bits_pp,
			&app->frame.line_length, &app->frame.endian);
	if (!app->frame.addr)
		error_close_app("Error: couldn't get the newly created image");
}

void	destroy_window(void)
{
	if (get_mlx() && get_frame()->img)
		mlx_destroy_image(get_mlx(), get_frame()->img);
	if (get_mlx() && get_app()->win)
		mlx_destroy_window(get_mlx(), get_app()->win);
}