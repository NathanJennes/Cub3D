/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_device.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:37:34 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/18 14:27:55 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	cub_update_mouse_pos(int x, int y)
{
	t_mlx	*app;

	app = get_app();
	app->mouse.position = ivec2(x, y);
}

t_ivec2	get_mouse_position(void)
{
	return (get_app()->mouse.position);
}
