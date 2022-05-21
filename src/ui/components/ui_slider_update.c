/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_slider_update.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:53:55 by njennes           #+#    #+#             */
/*   Updated: 2022/05/20 15:34:47 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"
#include "libft.h"
#include "input_code.h"

void	update_ui_slider(t_slider *slider)
{
	t_ui_component	*infos;
	t_ivec2			mouse_pos;
	float			percent;

	if (!slider->infos.displayed || !slider->selected)
		return ;
	infos = &slider->infos;
	mouse_pos = cub_get_mouse_position();
	if (mouse_pos.x < infos->pos.x + infos->size.y / 2)
		mouse_pos.x = infos->pos.x + infos->size.y / 2;
	else if (mouse_pos.x > infos->pos.x + infos->size.x - infos->size.y / 2)
		mouse_pos.x = infos->pos.x + infos->size.x - infos->size.y / 2;
	mouse_pos.x -= infos->pos.x + infos->size.y / 2;
	percent = (float)mouse_pos.x / (float)(infos->size.x - infos->size.y);
	slider->value = slider->min + percent * (slider->max - slider->min);
	slider->cursor_pos_x = mouse_pos.x;
}

void	update_ui_slider_click_begin(t_slider *slider, int mouse_btn)
{
	t_ui_component	*infos;
	t_ivec2			mouse_pos;

	if (!slider->infos.displayed || mouse_btn != MOUSE_LEFT)
		return ;
	infos = &slider->infos;
	mouse_pos = cub_get_mouse_position();
	if (mouse_pos.x >= infos->pos.x
		&& mouse_pos.x <= infos->pos.x + infos->size.x
		&& mouse_pos.y >= infos->pos.y
		&& mouse_pos.y <= infos->pos.y + infos->size.y)
	{
		slider->selected = TRUE;
		update_ui_slider(slider);
	}
}

void	update_ui_slider_click_end(t_slider *slider, int mouse_btn)
{
	if (!slider->infos.displayed || !slider->selected
		|| mouse_btn != MOUSE_LEFT)
		return ;
	slider->selected = FALSE;
}