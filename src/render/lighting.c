/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:04:44 by njennes           #+#    #+#             */
/*   Updated: 2022/05/28 16:45:11 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "render.h"

static void	process_light(t_light *light, t_ivec3 *lighting,
	t_vec3 *pos, t_vec3 *normal);

t_ivec3	get_lighting_level(t_vec3 pos, t_vec3 normal)
{
	t_mlx	*app;
	t_ivec3	lighting;
	t_light	*lights;
	int64_t	i;

	app = get_app();
	lights = get_lights();
	lighting = ivec3_zero();
	i = 0;
	while (i < app->gamestate.light_count)
	{
		process_light(&lights[i], &lighting, &pos, &normal);
		i++;
	}
	return (lighting);
}

int	apply_light_to_color(int color, t_ivec3 light)
{
	t_vec3	result;

	result.x = (double)get_r(color) * ((double)light.x / 255.0);
	result.y = (double)get_g(color) * ((double)light.y / 255.0);
	result.z = (double)get_b(color) * ((double)light.z / 255.0);
	vec3_clamp_max(&result, 255, 255, 255);
	return (trgb(get_t(color), (int)result.x, (int)result.y, (int)result.z));
}

static void	process_light(t_light *light, t_ivec3 *lighting,
	t_vec3 *pos, t_vec3 *normal)
{
	t_ray	ray;
	t_vec3	light_dir;
	t_vec3	dir_normalized;
	double	dot_product;
	double	distance;

	light_dir = vec3(light->pos.x - pos->x, light->pos.y - pos->y, light->pos.z - pos->z);
	dir_normalized = vec3_normalized(light_dir);
	ray = shoot_ray(vec2(dir_normalized.x, dir_normalized.y), vec2(pos->x, pos->y),
		ivec2((int64_t)pos->x / CELL_SIZE, (int64_t)pos->y / CELL_SIZE), RAY_LENGTH);
	ray.distance *= CELL_SIZE;
	if (ray.distance >= 0.0 && ray.distance * ray.distance < light_dir.x * light_dir.x + light_dir.y * light_dir.y)
		return ;
	dot_product = dir_normalized.x * normal->x + dir_normalized.y * normal->y + dir_normalized.z * normal->z;
	if (dot_product <= 0.0)
		return ;
	distance = ft_pow2(light_dir.x) + ft_pow2(light_dir.y) + ft_pow2(light_dir.z);
		ivec3_add(lighting, ivec3(
		(int64_t)((double)light->color.x * dot_product / distance * light->intensity),
		(int64_t)((double)light->color.y * dot_product / distance * light->intensity),
		(int64_t)((double)light->color.z * dot_product / distance * light->intensity)));
}
