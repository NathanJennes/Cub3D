/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:51:10 by cybattis          #+#    #+#             */
/*   Updated: 2022/04/22 14:52:04 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "core.h"

void	init_window(t_mlx *app, char *win_name)
{
	app->mlx = mlx_init();
	if (!app->mlx)
		error_close_app(app);
	app->win = mlx_new_window(app->mlx, WIN_W, WIN_H, win_name);
	if (!app->win)
	{
		free(app->mlx);
		error_close_app(app);
	}
	app->frame.img = mlx_new_image(app->mlx, WIN_W, WIN_H);
	if (!app->frame.img)
		error_close_app(app);
	app->frame.addr = mlx_get_data_addr(app->frame.img, &app->frame.bits_pp,
			&app->frame.line_length, &app->frame.endian);
	if (!app->frame.addr)
		error_close_app(app);
}

int	close_app(t_mlx *app)
{
	mlx_destroy_image(app->mlx, app->frame.img);
	mlx_destroy_window(app->mlx, app->win);
	free(app);
	exit(EXIT_SUCCESS);
}

void	error_close_app(t_mlx *app)
{
	if (app->mlx && app->frame.img)
		mlx_destroy_image(app->mlx, app->frame.img);
	if (app->mlx && app->win)
		mlx_destroy_window(app->mlx, app->win);
	free(app);
	exit(EXIT_FAILURE);
}
