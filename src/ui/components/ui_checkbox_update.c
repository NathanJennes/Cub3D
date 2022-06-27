/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_checkbox_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:36:40 by njennes           #+#    #+#             */
/*   Updated: 2022/06/27 17:44:44 by cybattis         ###   ########.fr       */
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
	mouse_pos = get_mouse_pos();
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
	mouse_pos = get_mouse_pos();
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

void	update_ui_checkbox_click_end(t_checkbox *ckx, int mouse_btn,
			t_ivec2 mouse_pos)
{
	t_ui_component	*component;

	if (!ckx->infos.displayed || !ckx->is_clickable || mouse_btn != MOUSE_LEFT)
		return ;
	component = &ckx->infos;
	if (mouse_pos.x >= component->pos.x && mouse_pos.x <= component->pos.x
		+ component->size.x && mouse_pos.y >= component->pos.y && mouse_pos.y
		<= component->pos.y + component->size.y && ckx->clicked)
	{
		if (ckx->checked)
		{
			ckx->checked = FALSE;
			ckx->clicked = FALSE;
			if (ckx->event_unchecked)
				ckx->event_unchecked(ckx);
		}
		else
		{
			ckx->checked = TRUE;
			ckx->clicked = FALSE;
			if (ckx->event_checked)
				ckx->event_checked(ckx);
		}
	}
	ckx->clicked = FALSE;
}
