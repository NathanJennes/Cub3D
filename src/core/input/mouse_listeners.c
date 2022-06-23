/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_listeners.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:31:13 by njennes           #+#    #+#             */
/*   Updated: 2022/05/28 16:27:57 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <stdlib.h>

void	update_ui_click_begin(int button);
void	update_ui_click_end(int button);

void	mouse_click_begin(int button)
{
	t_rgb	color;

	color.r = rand() % (255 - 1) + 1;
	color.g = rand() % (255 - 1) + 1;
	color.b = rand() % (255 - 1) + 1;
	update_ui_click_begin(button);
	add_light(&get_app()->gamestate,
		vec3(get_mouse_position().x, get_mouse_position().y, CELL_SIZE / 2),
		color,
		1000.0);
}

void	mouse_click_end(int button)
{
	update_ui_click_end(button);
}

void	mouse_wheel_up(void)
{
	return ;
}

void	mouse_wheel_down(void)
{
	return ;
}
