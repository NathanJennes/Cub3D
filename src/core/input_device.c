/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_device.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:37:34 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/12 21:55:30 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	cub_get_mouse_pos(int x, int y)
{
	t_mlx	*app;

	app = get_app();
	app->mouse.pos_x = x;
	app->mouse.pos_y = y;
	if (MOUSE_DEBUG)
		dprintf(STDERR_FILENO, "%d -- %d\n", app->mouse.pos_x, app->mouse.pos_y);
}
