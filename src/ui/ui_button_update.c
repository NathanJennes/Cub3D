/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_button_update.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:28:10 by njennes           #+#    #+#             */
/*   Updated: 2022/05/19 18:35:40 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

void	update_ui_button(t_button *button)
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
}

void	update_ui_button_click_begin(t_button *button)
{
	t_ivec2			mouse_pos;
	t_ui_component	*component;

	component = &button->infos;
	mouse_pos = cub_get_mouse_position();
	if (mouse_pos.x >= component->pos.x
		&& mouse_pos.x <= component->pos.x + component->size.x
		&& mouse_pos.y >= component->pos.y
		&& mouse_pos.y <= component->pos.y + component->size.y)
		button->clicked = TRUE;
	else
		button->clicked = FALSE;
}

void	update_ui_button_click_end(t_button *button)
{
	t_ivec2			mouse_pos;
	t_ui_component	*component;

	component = &button->infos;
	mouse_pos = cub_get_mouse_position();
	if (mouse_pos.x >= component->pos.x
		&& mouse_pos.x <= component->pos.x + component->size.x
		&& mouse_pos.y >= component->pos.y
		&& mouse_pos.y <= component->pos.y + component->size.y
		&& button->clicked)
	{
		button->clicked = FALSE;
		button->event(button);
	}
	button->clicked = FALSE;
}
