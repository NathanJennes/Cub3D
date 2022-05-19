/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:44:35 by njennes           #+#    #+#             */
/*   Updated: 2022/05/19 17:17:58 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"
#include "render.h"

static void	print_player_vector(void);
static void	test_rays(void);
void		render_test_scene(const t_mlx *app);

int	main_loop(void)
{
	t_mlx	*app;

	app = get_app();
	clear_screen(BKGD_COLOR);
	if (app->game_state & IN_GAME)
//		render_walls(60);
	render_test_scene(app);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	return (0);
}

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
	render_circle(v2_to_iv2(get_player()->pos), 10, YELLOW);
	print_player_vector();
	test_rays();
}

#include <math.h>

static void	test_rays(void)
{
	float		ray_angle;
	float		ray_angle_base;
	float		dist;
	int64_t		i;
	t_vec2		pos;
	t_ivec2		map_pos;
	t_vec2		line_end;

	ray_angle = ((float)60 / 180.0f) / (float)WIN_W;
	ray_angle_base = get_player()->direction + ((float)60 / 360.0f);
	while (ray_angle_base < 0.0f)
		ray_angle_base += 2.0f * PI;

	pos = get_player()->pos;
	vec2_divf(&pos, CELL_WIDTH);
	map_pos.x = (int)pos.x;
	map_pos.y = (int)pos.y;
	i = 0;
	while (i < WIN_W)
	{
		dist = shoot_ray(vec2(cosf(ray_angle_base), sinf(ray_angle_base)), pos, map_pos);
//		dist *= (float)cos(ray_angle_base);
		line_end = vec2(pos.x * dist * CELL_WIDTH, pos.y * dist * CELL_WIDTH);
		if (dist >= 0)
			render_line(v2_to_iv2(pos), v2_to_iv2(line_end), RED, RED);
		ray_angle_base += ray_angle;
		i++;
	}
}

static void	print_player_vector(void)
{
	t_vec2	player_pos;
	t_vec2	forward;
	t_vec2	right;

	player_pos = get_player()->pos;
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
