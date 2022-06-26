/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_listeners.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:31:13 by njennes           #+#    #+#             */
/*   Updated: 2022/06/26 16:40:34 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <stdlib.h>

void	update_ui_click_begin(int button);
void	update_ui_click_end(int button);

void	mouse_click_begin(int button)
{
	t_rgb		color;
	t_sprite	new_sprite;
	t_light		*new_light;

	color.r = rand() % (255 - 1) + 1;
	color.g = rand() % (255 - 1) + 1;
	color.b = rand() % (255 - 1) + 1;
	update_ui_click_begin(button);
	add_light(&get_app()->gamestate,
		vec3(get_mouse_position().x, get_mouse_position().y, 18),
		color,
		100.0);
	new_light = &get_app()->gamestate.lights[get_app()->gamestate.light_count - 1];
	new_sprite.tex_id = get_app()->lamp_tex_id;
	new_sprite.size = ivec2(3, 4);
	new_sprite.pos = vec3(get_mouse_position().x, get_mouse_position().y, 8);
	new_sprite.color = vec3((double)new_light->color.r / 255.0,
		(double)new_light->color.g / 255.0,
		(double)new_light->color.b / 255.0);
	add_sprite_to_current_game(new_sprite);
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
