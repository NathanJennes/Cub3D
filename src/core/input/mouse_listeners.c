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
	update_ui_click_begin(button);
	add_light(vec3(cub_get_mouse_position().x, cub_get_mouse_position().y, CELL_SIZE / 2),
		ivec3(rand() % (255 - 1) + 1, rand() % (255 - 1) + 1, rand() % (255 - 1) + 1),
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
