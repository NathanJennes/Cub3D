/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:36:36 by njennes           #+#    #+#             */
/*   Updated: 2022/05/14 16:03:46 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "core.h"
#include "leaky.h"

static int64_t	add_texture_to_array(t_texture texture);
static void		grow_texture_array(void);

int64_t	load_texture(char *path)
{
	t_xpm_file	xpm_file;
	t_texture	new_texture;
	int64_t		tex_id;

	if (!load_xpm(&xpm_file, path))
		return (INVALID_TEXTURE);
	new_texture = create_texture_from_xpm_file(xpm_file);
	tex_id = add_texture_to_array(new_texture);
	return (tex_id);
}

t_texture	*get_texture_from_id(int64_t tex_id)
{
	t_texture_manager	*tex_manager;

	tex_manager = &get_app()->texture_manager;
	if (tex_id >= tex_manager->tex_array_size || tex_id < 0)
		return (NULL);
	return (&tex_manager->tex_array[tex_id]);
}

void	unload_texture_manager(void)
{
	int64_t				i;
	t_texture_manager	*tex_manager;

	i = 0;
	tex_manager = &get_app()->texture_manager;
	while (i < tex_manager->tex_array_size)
	{
		free_texture(&tex_manager->tex_array[i]);
		i++;
	}
	gc_free(tex_manager->tex_array);
}

static int64_t	add_texture_to_array(t_texture texture)
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
	gc_memmove(new_array, tex_manager->tex_array, tex_manager->tex_array_size);
	gc_free(tex_manager->tex_array);
	tex_manager->tex_array = new_array;
}
