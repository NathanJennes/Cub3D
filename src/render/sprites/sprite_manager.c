/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 13:37:13 by njennes           #+#    #+#             */
/*   Updated: 2022/06/10 14:00:30 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "core.h"
#include "leaky.h"

static void	generate_lookup_table(double *table);

void	init_sprite_manager(void)
{
	t_sprite_manager	*manager;

	manager = &get_app()->sprite_manager;
	manager->sprite_count = 1;
	manager->sprites = gc_calloc(1, sizeof (t_sprite));
	manager->sprites[0] = (t_sprite){{120, 80}, {10, 10}, 0};
	manager->angle_lookup = gc_calloc(get_settings()->win_w, sizeof (double));
	generate_lookup_table(manager->angle_lookup);
}

void	clear_sprite_manager(void)
{
	t_sprite_manager	*manager;

	manager = &get_app()->sprite_manager;
	gc_free(manager->sprites);
	gc_free(manager->angle_lookup);
}

static void	generate_lookup_table(double *table)
{
	t_settings	*settings;
	t_player	*player;
	int64_t		i;
	t_vec2		ray;
	t_vec2		start;
	double		angle;

	player = get_player();
	settings = get_settings();
	start = vec2(player->world_pos.x + player->forward.x
				 - player->right.x * (get_math()->plane_len),
				player->world_pos.y + player->forward.y
				- player->right.y * (get_math()->plane_len));
	i = 0;
	while (i < settings->win_w)
	{
		ray = \
			vec2(start.x - player->world_pos.x, start.y - player->world_pos.y);
		vec2_normalize(&ray);
		angle = atan2(player->forward.x * ray.y - player->forward.y * ray.x, player->forward.x * ray.x + player->forward.y * ray.y);
		table[i] = angle;
		vec2_add(&start, player->plane_inc);
		i++;
	}
}
