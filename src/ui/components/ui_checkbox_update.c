/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_checkbox_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:36:40 by njennes           #+#    #+#             */
/*   Updated: 2022/06/01 13:09:32 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"
#include "input_code.h"

void	update_ui_checkbox(t_checkbox *checkbox)
{
	t_ivec2			mouse_pos;
	t_ui_component	*component;

	if (!checkbox->infos.displayed)
		return ;
	component = &checkbox->infos;
	mouse_pos = get_mouse_position();
	if (mouse_pos.x >= component->pos.x
		&& mouse_pos.x <= component->pos.x + component->size.x
		&& mouse_pos.y >= component->pos.y
		&& mouse_pos.y <= component->pos.y + component->size.y)
		checkbox->hovered = TRUE;
	else
		checkbox->hovered = FALSE;
}

void	update_ui_checkbox_click_begin(t_checkbox *checkbox, int mouse_btn)
{
	t_ivec2			mouse_pos;
	t_ui_component	*component;

	if (!checkbox->infos.displayed || !checkbox->is_clickable
		|| mouse_btn != MOUSE_LEFT)
		return ;
	component = &checkbox->infos;
	mouse_pos = get_mouse_position();
	if (mouse_pos.x >= component->pos.x
		&& mouse_pos.x <= component->pos.x + component->size.x
		&& mouse_pos.y >= component->pos.y
		&& mouse_pos.y <= component->pos.y + component->size.y)
	{
		checkbox->clicked = TRUE;
	}
	else
		checkbox->clicked = FALSE;
}

void	update_ui_checkbox_click_end(t_checkbox *checkbox, int mouse_btn)
{
	t_ivec2			mouse_pos;
	t_ui_component	*component;

	if (!checkbox->infos.displayed || !checkbox->is_clickable
		|| mouse_btn != MOUSE_LEFT)
		return ;
	component = &checkbox->infos;
	mouse_pos = get_mouse_position();
	if (mouse_pos.x >= component->pos.x
		&& mouse_pos.x <= component->pos.x + component->size.x
		&& mouse_pos.y >= component->pos.y
		&& mouse_pos.y <= component->pos.y + component->size.y
		&& checkbox->clicked)
	{
		if (checkbox->checked)
		{
			checkbox->checked = FALSE;
			checkbox->clicked = FALSE;
			if (checkbox->event_unchecked)
				checkbox->event_unchecked(checkbox);
		}
		else
		{
			checkbox->checked = TRUE;
			checkbox->clicked = FALSE;
			if (checkbox->event_checked)
				checkbox->event_checked(checkbox);
		}
	}
	checkbox->clicked = FALSE;
}
