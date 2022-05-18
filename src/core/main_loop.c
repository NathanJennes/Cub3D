/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:44:35 by njennes           #+#    #+#             */
/*   Updated: 2022/05/18 19:51:04 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"
#include "render.h"

int	main_loop(void)
{
	t_mlx	*app;

	app = get_app();
	if (app->game_state & IN_GAME){}
		// game frame
	clear_screen(BKGD_COLOR);
	if (app->game_state & MENU){}
		//render_ui();
	render_scene(app);
	test_ray();
	print_player_vector();
	render_walls(70);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	return (0);
}

void	print_player_vector(void)
{
	t_vec2	player_pos;
	t_vec2	forward;
	t_vec2	right;

	player_pos = get_player()->pos;
	forward = get_player()->forward;
	right = get_player()->right;
	ft_print_vec2(right);
	render_line(v2_to_iv2(player_pos), ivec2(player_pos.x + forward.x * 50,
			player_pos.y + forward.y * 50), BLACK, BLACK);
	render_line(v2_to_iv2(player_pos), ivec2(player_pos.x + right.x * 50,
			player_pos.y + right.y * 50), BLACK, BLACK);
	render_line(v2_to_iv2(player_pos), ivec2(player_pos.x - right.x * 50,
			player_pos.y - right.y * 50), BLACK, BLACK);
}

void	test_ray(void)
{
	float	dist;
	t_vec2	line_end;
	t_ivec2	map_pos;
	t_vec2	player_pos = get_player()->pos;
	t_ivec2	mouse_pos = cub_get_mouse_position();
	t_vec2	ray = vec2(mouse_pos.x - player_pos.x, mouse_pos.y - player_pos.y);

	vec2_normalize(&ray);
	vec2_divf(&player_pos, CELL_WIDTH);
	map_pos.x = (int)player_pos.x;
	map_pos.y = (int)player_pos.y;
	dist = shoot_ray(ray, player_pos, map_pos);
	player_pos = get_player()->pos;
	line_end = vec2(player_pos.x + ray.x * dist * CELL_WIDTH, player_pos.y + ray.y * dist * CELL_WIDTH);
	if (dist >= 0)
		render_line(v2_to_iv2(player_pos), v2_to_iv2(line_end), create_trgb(0, 255, 0, 0), create_trgb(0, 255, 0, 0));
}

void	render_scene(const t_mlx *app)
{
	int			color;
	t_map_info	*map = &app->gamestate.map;

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
			render_rect(ivec2(j * CELL_WIDTH, i * CELL_WIDTH), ivec2(CELL_WIDTH, CELL_WIDTH), color);
		}
	}
	render_circle(v2_to_iv2(get_player()->pos), 20, create_trgb(0, 0, 255, 0));
	render_circle(cub_get_mouse_position(), 20, create_trgb(0, 255, 0, 0));
}
