/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_device.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyril <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:37:34 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/14 00:09:22 by Cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	cub_update_mouse_pos(int x, int y)
{
	t_mlx	*app;

	app = get_app();
	app->mouse.position = ivec2(x, y);
}

t_ivec2	get_mouse_pos(void)
{
	return (get_app()->mouse.position);
}

void	reset_mouse_pos(void)
{
	t_mlx	*app;

	app = get_app();
	mlx_mouse_move(app->win, app->settings.halfw_w, app->settings.halfw_h);
	cub_update_mouse_pos(app->settings.halfw_w, app->settings.halfw_h);
}
