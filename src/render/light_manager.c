/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:43:56 by njennes           #+#    #+#             */
/*   Updated: 2022/05/27 15:56:11 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "core.h"
#include "leaky.h"

void	add_light(t_vec3 pos, t_ivec3 color, double intensity)
{
	t_mlx	*app;
	t_light	*new;

	app = get_app();
	new = gc_calloc(app->gamestate.light_count + 1, sizeof (t_light));
	gc_memmove(new, app->gamestate.lights, app->gamestate.light_count * sizeof (t_light));
	gc_free(app->gamestate.lights);
	app->gamestate.lights = new;
	app->gamestate.lights[app->gamestate.light_count] = (t_light){pos, color, intensity};
	app->gamestate.light_count++;
}

void	free_lights(t_gamestate *gamestate)
{
	gc_free(gamestate->lights);
}
