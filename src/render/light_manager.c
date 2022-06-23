/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:43:56 by njennes           #+#    #+#             */
/*   Updated: 2022/06/15 14:35:59 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "core.h"
#include "leaky.h"

void	add_light(t_gamestate *gamestate, t_vec3 pos, t_rgb color, double intensity)
{
	t_mlx	*app;
	t_light	*new;

	app = get_app();
	new = gc_calloc(gamestate->light_count + 1, sizeof (t_light));
	gc_memmove(new, gamestate->lights, gamestate->light_count * sizeof (t_light));
	gc_free(gamestate->lights);
	gamestate->lights = new;
	gamestate->lights[gamestate->light_count] = (t_light){pos, color, intensity};
	gamestate->light_count++;
}

void	free_lights(t_gamestate *gamestate)
{
	gc_free(gamestate->lights);
}
