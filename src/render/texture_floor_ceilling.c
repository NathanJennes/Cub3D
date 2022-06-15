/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_floor_ceilling.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:05:06 by Cyril             #+#    #+#             */
/*   Updated: 2022/06/15 14:06:42 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "texture.h"
#include "render.h"
#include <math.h>

//static double	get_texture_position(t_texture *texture, t_vec2 hit);

//void	render_floor(t_ivec2 pos, t_wall wall, t_ivec3 lighting)
//{
//	double		dist;
//	t_texture	*tx_floor;
//	int64_t		px;
//	int32_t		px_color;
//	t_vec2		floor_pos;
//
//	tx_floor = get_texture_from_id(get_map_infos()->tx_list[4]);
//	while (pos.y < get_settings()->win_h)
//	{
//		dist = tan(get_math()->r_vfov / 2) * CELL_SIZE / 2;
//		printf("Dist %lf\n", dist);
//		px = (int64_t)get_texture_position(tx_floor, floor_pos);
//		px_color = get_pixel_color_from_texture(px, pos.y, tx_floor->ao_flat);
//		px_color = apply_light_to_color(px_color, lighting);
//		set_screen_pixel(pos.x, pos.y + wall.origin, px_color);
//		pos.y++;
//	}
//}

//static double	get_texture_position(t_texture *texture, t_vec2 hit)
//{
//	double		pos_x;
//	int64_t		ratio;
//
//	ratio = (int64_t)hit.y / CELL_SIZE;
//	pos_x = hit.y - (double)(ratio * CELL_SIZE);
//	return ((pos_x / (double)CELL_SIZE) * (double)texture->width);
//}
