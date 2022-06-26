/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_listeners.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:31:13 by njennes           #+#    #+#             */
/*   Updated: 2022/06/26 17:01:23 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <stdlib.h>

void	update_ui_click_begin(int button);
void	update_ui_click_end(int button);

void	mouse_click_begin(int button)
{
	t_ui_map_menu	*map_menu;
	t_rgb			color;

	update_ui_click_begin(button);
	if (get_app()->editor_mode == TRUE)
	{
		map_menu = &get_ui()->map_menu;
		color.r = (uint8_t)map_menu->slid_red_color.value;
		color.g = (uint8_t)map_menu->slid_green_color.value;
		color.b = (uint8_t)map_menu->slid_blue_color.value;
		add_light(&get_app()->gamestate,
			vec3((double)get_mouse_position().x,
				(double)get_mouse_position().y, CELL_SIZE / 2.0), color, 100.0);
	}
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
