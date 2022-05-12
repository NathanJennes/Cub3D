/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_device.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:37:34 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/12 11:31:32 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	get_mouse_pos(t_mlx *app)
{
#ifdef __linux__
	mlx_mouse_get_pos(app->mlx, app->win, &app->mouse.pos_x, &app->mouse.pos_y);
#else
	mlx_mouse_get_pos(app->win, &app->mouse.pos_x, &app->mouse.pos_y);
#endif
	if (MOUSE_DEBUG)
		dprintf(STDERR_FILENO, "%d -- %d\n", app->mouse.pos_x, app->mouse.pos_y);
}
