/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyril <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:09:46 by Cyril             #+#    #+#             */
/*   Updated: 2022/06/25 18:16:10 by Cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"
#include "render.h"

inline static void	print_light(const t_mlx *app);
inline static void	render_map(const t_map_info *map, t_mlx *app);

void	render_map_menu(void)
{
	t_mlx			*app;
	t_ui_map_menu	*menu;

	app = get_app();
	menu = &app->ui.map_menu;
	render_map(get_map_infos(), app);
	render_ui_checkbox(&menu->chk_editor_mode);
	render_ui_slider(&menu->intensity);
	render_ui_slider(&menu->slid_blue_color);
	render_ui_slider(&menu->slid_green_color);
	render_ui_slider(&menu->slid_red_color);
	render_ui_label(&menu->intensity_label);
	render_ui_label(&menu->blue_label);
	render_ui_label(&menu->green_label);
	render_ui_label(&menu->red_label);
	render_ui_button(&menu->add_light);
	render_ui_button(&menu->delete_light);
}

inline static void	render_map(const t_map_info *map, t_mlx *app)
{
	t_ivec2	p;

	p.y = 0;
	while (p.y < map->height)
	{
		p.x = 0;
		while (p.x < map->width)
		{
			if (map->map[p.y][p.x] == WALL)
				draw_rect(ivec2(p.x * CELL_SIZE, p.y * CELL_SIZE), \
					ivec2(CELL_SIZE, CELL_SIZE), BLACK);
			else if (map->map[p.y][p.x] == EMPTY)
				draw_rect(ivec2(p.x * CELL_SIZE, p.y * CELL_SIZE), \
					ivec2(CELL_SIZE, CELL_SIZE), DARK_GREY);
			p.x++;
		}
		p.y++;
	}
	if (app->editor_mode == TRUE)
		print_light(app);
	draw_circle(v2_to_iv2(get_player()->world_pos), MMAP_PLAYER_DIAM, GREEN);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
}

inline static void	print_light(const t_mlx *app)
{
	int64_t	i;
	t_light	*l;

	i = 0;
	while (i < app->gamestate.light_count)
	{
		l = &app->gamestate.lights[i];
		draw_circle(ivec2((int64_t)l->pos.x, (int64_t)l->pos.y), 7,
			(int)l->color.color);
		i++;
	}
}
