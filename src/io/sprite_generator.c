/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_generator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:38:35 by njennes           #+#    #+#             */
/*   Updated: 2022/06/26 16:36:53 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"
#include "io.h"

void	generate_sprites_for_new_map(void)
{
	t_gamestate	*save;
	t_sprite	new_sprite;
	int64_t		i;

	init_sprite_manager();
	save = &get_app()->gamestate;
	i = 0;
	while (i < save->light_count)
	{
		new_sprite.tex_id = get_app()->lamp_tex_id;
		new_sprite.size = ivec2(3, 4);
		new_sprite.pos = vec3(save->lights[i].pos.x, save->lights[i].pos.y, 8);
		new_sprite.color = vec3((double)save->lights[i].color.r / 255.0,
				(double)save->lights[i].color.g / 255.0,
				(double)save->lights[i].color.b / 255.0);
		add_sprite_to_current_game(new_sprite);
		i++;
	}
}
