/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:40:35 by njennes           #+#    #+#             */
/*   Updated: 2022/05/25 17:55:39 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"
#include "render.h"

static void	add_font(char *meta_path, char *bitmap_path);
static void	grow_font_array(t_font_manager *manager);

void	init_font_manager(void)
{
	add_font("assets/ui/cube-export/test_font_2.fnt",
		"assets/ui/cube-export/test_font_2.png");
}

t_font	*get_font(char *name)
{
	t_font_manager	*manager;
	int64_t			i;

	manager = &get_app()->font_manager;
	i = 0;
	while (i < manager->font_count)
	{
		if (ft_strcmp(name, manager->fonts[i].name) == 0)
			return (&manager->fonts[i]);
		i++;
	}
	return (NULL);
}

void	unload_font_manager(void)
{
	t_font_manager	*manager;
	int64_t			i;

	manager = &get_app()->font_manager;
	i = 0;
	while (i < manager->font_count)
	{
		unload_bitmap_font(&manager->fonts[i].bitmap);
		gc_free(manager->fonts[i].name);
		i++;
	}
}

static void	add_font(char *meta_path, char *bitmap_path)
{
	t_font			new_font;
	t_font_manager	*manager;

	manager = &get_app()->font_manager;
	ft_memset(&new_font, 0, sizeof (t_font));
	new_font.bitmap = load_bitmap_font(bitmap_path);
	if (!new_font.bitmap.data)
		return ;
	if (!load_font_meta(&new_font, meta_path))
		return ;
	grow_font_array(manager);
	manager->fonts[manager->font_count - 1] = new_font;
}

static void	grow_font_array(t_font_manager *manager)
{
	t_font	*new;

	if (!manager->fonts)
		manager->fonts = gc_calloc(1, sizeof (t_font));
	else
	{
		new = gc_calloc(manager->font_count + 1, sizeof (t_font));
		gc_memmove(new, manager->fonts, manager->font_count * sizeof (t_font));
		gc_free(manager->fonts);
		manager->fonts = new;
	}
	manager->font_count++;
}
