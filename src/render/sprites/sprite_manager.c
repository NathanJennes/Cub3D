/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 13:37:13 by njennes           #+#    #+#             */
/*   Updated: 2022/06/27 15:45:15 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "core.h"
#include "leaky.h"
#include "render.h"

inline static void	generate_lookup_table(double *table, t_settings *settings);

void	init_sprite_manager(void)
{
	t_sprite_manager	*manager;
	t_settings			*settings;

	settings = get_settings();
	manager = &get_app()->sprite_manager;
	gc_free(manager->sprites);
	gc_free(manager->angle_lookup);
	manager->sprite_count = 0;
	manager->sprites = gc_calloc(0, sizeof (t_sprite));
	manager->angle_lookup = gc_calloc(get_settings()->win_w, sizeof (double));
	generate_lookup_table(manager->angle_lookup, settings);
}

void	add_sprite_to_current_game(t_sprite sprite)
{
	t_sprite			*new_array;
	t_sprite_manager	*manager;

	manager = &get_app()->sprite_manager;
	new_array = gc_calloc(manager->sprite_count + 1, sizeof (t_sprite));
	ft_memmove(new_array, manager->sprites,
		manager->sprite_count * sizeof (t_sprite));
	gc_free(manager->sprites);
	manager->sprites = new_array;
	sprite.id = manager->sprite_count;
	manager->sprites[manager->sprite_count] = sprite;
	manager->sprite_count++;
}

void	clear_sprite_manager(void)
{
	t_sprite_manager	*manager;

	manager = &get_app()->sprite_manager;
	manager->sprite_count = 0;
	gc_free(manager->sprites);
	gc_free(manager->angle_lookup);
}

void	render_sprites(void)
{
	t_sprite_manager	*manager;
	int64_t				i;

	manager = &get_app()->sprite_manager;
	i = 0;
	while (i < manager->sprite_count)
	{
		render_sprite(&manager->sprites[i]);
		i++;
	}
}

inline static void	generate_lookup_table(double *table, t_settings *settings)
{
	t_player	*player;
	int64_t		i;
	t_vec2		ray;
	t_vec2		start;
	double		angle;

	player = get_player();
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
		angle = atan2(player->forward.x * ray.y - player->forward.y * ray.x,
				player->forward.x * ray.x + player->forward.y * ray.y);
		table[i] = angle;
		vec2_add(&start, player->plane_inc);
		i++;
	}
}
