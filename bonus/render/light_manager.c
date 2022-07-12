/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:43:56 by njennes           #+#    #+#             */
/*   Updated: 2022/06/29 14:59:06 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "core.h"

void	add_light(t_gamestate *gamestate, t_vec3 pos, t_rgb color,
		double intensity)
{
	t_light	*new;

	new = gc_calloc(gamestate->light_count + 1, sizeof (t_light));
	ft_memmove(new, gamestate->lights,
		gamestate->light_count * sizeof(t_light));
	gc_free(gamestate->lights);
	gamestate->lights = new;
	gamestate->lights[gamestate->light_count] = \
		(t_light){pos, color, intensity, TRUE};
	gamestate->light_count++;
}

void	delete_light(t_gamestate *gamestate, int64_t id)
{
	void	*light_to_delete;
	void	*sprite_to_delete;
	t_mlx	*app;

	app = get_app();
	light_to_delete = &gamestate->lights[id];
	ft_memmove(light_to_delete, light_to_delete + sizeof (t_light),
		(gamestate->light_count - id - 1) * sizeof (t_light));
	gamestate->light_count--;
	sprite_to_delete = &app->sprite_manager.sprites[id];
	ft_memmove(sprite_to_delete, sprite_to_delete + sizeof (t_sprite),
		(app->sprite_manager.sprite_count - id - 1) * sizeof (t_sprite));
	app->sprite_manager.sprite_count--;
}

void	free_lights(t_gamestate *gamestate)
{
	gc_free(gamestate->lights);
}
