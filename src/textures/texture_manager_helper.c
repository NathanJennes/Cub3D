/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manager_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:19:14 by njennes           #+#    #+#             */
/*   Updated: 2022/06/15 14:35:59 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "core.h"
#include "leaky.h"

static void	grow_texture_array(void);

int64_t	add_texture_to_array(t_texture texture)
{
	t_mlx				*app;
	t_texture_manager	*tex_manager;
	int64_t				tex_id;

	app = get_app();
	tex_manager = &app->texture_manager;
	if (!tex_manager->tex_array)
		tex_manager->tex_array = gc_calloc(1, sizeof (t_texture));
	else
		grow_texture_array();
	tex_id = tex_manager->tex_array_size;
	tex_manager->tex_array[tex_id] = texture;
	tex_manager->tex_array_size++;
	return (tex_id);
}

static void	grow_texture_array(void)
{
	t_texture			*new_array;
	t_texture_manager	*tex_manager;

	tex_manager = &get_app()->texture_manager;
	new_array = gc_calloc(tex_manager->tex_array_size + 1, sizeof (t_texture));
	gc_memmove(new_array, tex_manager->tex_array,
		tex_manager->tex_array_size * sizeof (t_texture));
	gc_free(tex_manager->tex_array);
	tex_manager->tex_array = new_array;
}
