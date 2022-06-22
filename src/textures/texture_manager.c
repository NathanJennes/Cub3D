/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:36:36 by njennes           #+#    #+#             */
/*   Updated: 2022/06/17 15:23:27 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "core.h"
#include "leaky.h"
#include "render.h"

int64_t	add_texture_to_array(t_texture texture);

inline static int64_t	get_texture_id_from_name(char *name);

void	init_texture_manager(void)
{
	int64_t				base_tex;

	base_tex = new_texture(128, 128);
	draw_rect_tex(ivec2(0, 0), ivec2(128, 128),
		trgb(0, 170, 155, 125), base_tex);
	finish_new_texture(base_tex);
}

int64_t	load_texture(char *path)
{
	t_xpm_file	xpm_file;
	t_texture	new_texture;
	int64_t		tex_id;

	if (!path)
		return (INVALID_TEXTURE);
	tex_id = get_texture_id_from_name(path);
	if (tex_id != INVALID_TEXTURE)
		return (tex_id);
	if (!load_xpm(&xpm_file, path))
		return (INVALID_TEXTURE);
	new_texture = create_texture_from_xpm_file(xpm_file);
	new_texture.name = gc_strdup(path);
	tex_id = add_texture_to_array(new_texture);
	return (tex_id);
}

int64_t	new_texture(int width, int height)
{
	t_texture	new_texture;
	int64_t		tex_id;

	new_texture = create_blank_texture(width, height);
	new_texture.name = NULL;
	tex_id = add_texture_to_array(new_texture);
	return (tex_id);
}

t_texture	*get_texture_from_id(int64_t tex_id)
{
	t_texture_manager	*tex_manager;

	tex_manager = &get_app()->texture_manager;
	if (tex_id >= tex_manager->tex_array_size || tex_id < 0)
		return (&tex_manager->tex_array[0]);
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

inline static int64_t	get_texture_id_from_name(char *name)
{
	int64_t				i;
	t_texture_manager	*tex_manager;

	i = 0;
	tex_manager = &get_app()->texture_manager;
	while (i < tex_manager->tex_array_size)
	{
		if (ft_strcmp(name, tex_manager->tex_array[i].name) == 0)
			return (i);
		i++;
	}
	return (INVALID_TEXTURE);
}
