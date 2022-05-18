/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_button.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 22:30:28 by njennes           #+#    #+#             */
/*   Updated: 2022/05/18 15:15:12 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"
#include "render.h"

//TODO: refactor to uniformize ui creation prototypes
t_button	create_button(int64_t tex_id,
		t_ivec2 pos,
		int (*event)(struct s_button *button),
		t_bool displayed)
{
	t_button	button;

	ft_memset(&button, 0, sizeof (t_button));
	button.infos.pos = pos;
	button.infos.size = get_texture_size(tex_id);
	button.infos.displayed = displayed;
	button.tex_id = tex_id;
	button.event = event;
	button.hovered = FALSE;
	button.clicked = FALSE;
	button.is_clickable = TRUE;
	return (button);
}

void	ui_button_update(t_button *button, t_bool mouse_clicked)
{
	t_ivec2			mouse_pos;
	t_ui_component	*component;

	component = &button->infos;
	mouse_pos = cub_get_mouse_position();
	if (mouse_pos.x >= component->pos.x
		&& mouse_pos.x <= component->pos.x + component->size.x
		&& mouse_pos.y >= component->pos.y
		&& mouse_pos.y <= component->pos.y + component->size.y)
		button->hovered = TRUE;
	else
		button->hovered = FALSE;
	if (button->hovered && mouse_clicked)
	{
		button->clicked = TRUE;
		button->event(button);
	}
	else
		button->clicked = FALSE;
}

void	render_ui_button(t_button *button)
{
	t_ui_component	*infos;

	if (!button->infos.displayed)
		return ;
	infos = &button->infos;
	if (button->clicked)
		render_ui_texture_grayscale(button->tex_id, infos->pos.x, infos->pos.y);
	else if (button->hovered)
		render_ui_texture_inversed(button->tex_id, infos->pos.x, infos->pos.y);
	else
		render_ui_texture(button->tex_id, infos->pos.x, infos->pos.y);
}
