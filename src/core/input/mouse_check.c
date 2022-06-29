/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:42:37 by Cyril             #+#    #+#             */
/*   Updated: 2022/06/29 15:02:23 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"

inline static double	simple_dist(t_vec3 a, t_vec3 b);

int	is_light_inside_map(t_ivec2 mouse_pos)
{
	int64_t		x;
	int64_t		y;
	t_map_info	*map;

	map = get_map_infos();
	x = mouse_pos.x / CELL_SIZE;
	y = mouse_pos.y / CELL_SIZE;
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	if (map->map[y][x] != EMPTY)
		return (0);
	return (1);
}

void	delete_lights_in_minimap(void)
{
	int64_t		i;
	t_ivec2		mouse_pos;
	t_light		*light;
	t_gamestate	*gamestate;

	i = 0;
	mouse_pos = get_mouse_pos();
	gamestate = get_gamestate();
	while (i < gamestate->light_count)
	{
		light = &gamestate->lights[i];
		if (simple_dist(light->pos,
			vec3(mouse_pos.x, mouse_pos.y, light->pos.z))
			<= (CELL_SIZE / 2) * (CELL_SIZE / 2))
		{
			delete_light(gamestate, i);
			if (i > 0)
				i--;
		}
		else
			i++;
	}
}

inline static double	simple_dist(t_vec3 a, t_vec3 b)
{
	return (ft_pow2(a.x - b.x) + ft_pow2(a.y - b.y) + ft_pow2(a.z - b.z));
}
