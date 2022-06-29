/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_wall_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:14:33 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/27 17:20:13 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"
#include "texture.h"

double	get_texture_position(t_texture *texture, t_ray *ray)
{
	double		pos_x;
	int64_t		ratio;

	pos_x = 0;
	if (ray->side == SIDE_X)
	{
		ratio = (int64_t)ray->hit_pos.y / CELL_SIZE;
		pos_x = ray->hit_pos.y - (double)(ratio * CELL_SIZE);
	}
	else if (ray->side == SIDE_Y)
	{
		ratio = (int64_t)ray->hit_pos.x / CELL_SIZE;
		pos_x = ray->hit_pos.x - (double)(ratio * CELL_SIZE);
	}
	return ((pos_x / (double)CELL_SIZE) * (double)texture->width);
}

t_texture	*get_face_texture(t_ray *ray, t_rgb ***tx_data, t_texture *texture)
{
	if (ray->side == SIDE_X)
	{
		if (ray->hit_pos.x < get_player()->world_pos.x)
		{
			texture = get_texture_from_id(get_map_infos()->tx_list[WEST]);
			*tx_data = texture->wall_flip;
			return (texture);
		}
		else
			texture = get_texture_from_id(get_map_infos()->tx_list[EAST]);
	}
	else
	{
		if (ray->hit_pos.y < get_player()->world_pos.y)
			texture = get_texture_from_id(get_map_infos()->tx_list[NORTH]);
		else
		{
			texture = get_texture_from_id(get_map_infos()->tx_list[SOUTH]);
			*tx_data = texture->wall_flip;
			return (texture);
		}
	}
	*tx_data = texture->wall;
	return (texture);
}
