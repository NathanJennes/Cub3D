/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_button.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 22:30:28 by njennes           #+#    #+#             */
/*   Updated: 2022/05/16 22:48:30 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

t_button	create_button(int64_t tex_id,
		t_vec2 pos,
		int (*event)(struct s_button *button),
		t_bool displayed)
{
	t_button	button;

	button.tex_id = tex_id;
	button.position = pos;
	button.event = event;
	button.displayed = displayed;
	button.hovered = FALSE;
	button.clicked = FALSE;
	button.is_clickable = TRUE;
	button.bounding_box = get_texture_size(tex_id);
	return (button);
}

void	ui_button_update(t_button *button, t_bool mouse_clicked)
{
	t_vec2	mouse_pos;

	mouse_pos = cub_get_mouse_pos();
	if (mouse_pos.x >= button->position.x && mouse_pos.x <= button->position.x + button->bounding_box.x
		&& mouse_pos.y >= button->position.y && mouse_pos.y <= button->position.y + button->bounding_box.y)
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
