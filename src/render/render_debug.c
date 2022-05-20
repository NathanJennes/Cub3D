/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:21:01 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/20 14:44:08 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"
#include "render.h"
#include <math.h>

static t_vec2	rotate_vector(t_vec2 v, float angle);
static void		print_player_vector(void);
static void		debug_rays(void);

void	render_test_scene(const t_mlx *app)
{
	int					color;
	const t_map_info	*map = &app->gamestate.map;

	for (int64_t i = 0; i < map->height; i++)
	{
		for (int64_t j = 0; j < map->width; j++)
		{
			if (map->map[i][j] == WALL)
				color = create_trgb(0, 51, 51, 51);
			else if (map->map[i][j] == EMPTY)
				color = create_trgb(0, 200, 200, 200);
			else
				color = create_trgb(0, 0, 0, 0);
			render_rect(ivec2(j * CELL_WIDTH, i * CELL_WIDTH),
				ivec2(CELL_WIDTH, CELL_WIDTH), color);
		}
	}
	render_circle(v2_to_iv2(get_player()->world_pos), 10, YELLOW);
	print_player_vector();
	debug_rays();
}

static void	debug_rays(void)
{
}

void	print_player_vector(void)
{
	t_vec2	player_pos;
	t_vec2	forward;
	t_vec2	right;

	player_pos = get_player()->world_pos;
	forward = get_player()->forward;
	right = get_player()->right;
//	ft_print_vec2(right);
	render_line(v2_to_iv2(player_pos),
			ivec2(player_pos.x + forward.x * CELL_WIDTH,
					player_pos.y + forward.y * CELL_WIDTH), BLACK, BLACK);
	render_line(v2_to_iv2(player_pos),
			ivec2(player_pos.x + right.x * CELL_WIDTH,
					player_pos.y + right.y * CELL_WIDTH), BLUE, BLUE);
	render_line(v2_to_iv2(player_pos),
			ivec2(player_pos.x - right.x * CELL_WIDTH,
					player_pos.y - right.y * CELL_WIDTH), GREEN, GREEN);
}

static t_vec2	rotate_vector(t_vec2 v, float angle)
{
	t_vec2	new_vector;

	new_vector.x = v.x * cos(angle) - v.y * sin(angle);
	new_vector.y = v.x * -sin(angle) + v.y * cos(angle);
	return (new_vector);
}

//TODO: - grid map_pos
//		- distance
//		- world_pos
