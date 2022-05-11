/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_device.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:37:34 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/10 21:43:09 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	get_mouse_pos(t_mlx *app)
{
	mlx_mouse_get_pos(app->win, &app->mouse.pos_x, &app->mouse.pos_y);
	if (MOUSE_DEBUG)
		dprintf(STDERR_FILENO, "%d -- %d\n", app->mouse.pos_x, app->mouse.pos_y);
}
