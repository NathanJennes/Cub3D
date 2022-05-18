/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:44:35 by njennes           #+#    #+#             */
/*   Updated: 2022/05/18 13:13:03 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"
#include "render.h"

void render_scene(const t_mlx *app);

int	main_loop(void)
{
	t_mlx	*app;

	app = get_app();
	if (app->game_state & IN_GAME){}
		// game frame
	clear_screen(BKGD_COLOR);
	//render_ui();
	//render_walls(90);
	render_scene(app);

	t_vec2	mouse_pos = cub_get_mouse_pos();
	t_vec2	player_pos = get_player()->pos;
	t_vec2	ray = vec2(mouse_pos.x - player_pos.x, mouse_pos.y - player_pos.y);
	vec2_normalize(&ray);

	t_ivec2	map_pos;
	vec2_divf(&player_pos, CELL_WIDTH);
	map_pos.x = (int)player_pos.x;
	map_pos.y = (int)player_pos.y;
	float dist = shoot_ray(ray, player_pos, map_pos);
	player_pos = get_player()->pos;
	t_vec2	line_end = vec2(player_pos.x + ray.x * dist * CELL_WIDTH, player_pos.y + ray.y * dist * CELL_WIDTH);
	if (dist >= 0)
		render_line(player_pos, line_end, create_trgb(0, 255, 0, 0), create_trgb(0, 255, 0, 0));

	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	return (0);
}

void render_scene(const t_mlx *app)
{
	t_map_info *map = &app->gamestate.map;
	for (size_t i = 0; i < map->height; i++)
	{
		for (size_t j = 0; j < map->width; j++)
		{
			int color;
			if (map->map[i][j] == WALL)
				color = create_trgb(0, 51, 51, 51);
			else if (map->map[i][j] == EMPTY)
				color = create_trgb(0, 200, 200, 200);
			else
				color = create_trgb(0, 0, 0, 0);
			render_rect(vec2(j * CELL_WIDTH, i * CELL_WIDTH), vec2(CELL_WIDTH, CELL_WIDTH), color);
		}
	}
	render_circle(get_player()->pos, 20, create_trgb(0, 0, 255, 0));
	render_circle(cub_get_mouse_pos(), 20, create_trgb(0, 255, 0, 0));
}
