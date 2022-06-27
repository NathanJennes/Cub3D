/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_slider_update.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:53:55 by njennes           #+#    #+#             */
/*   Updated: 2022/06/10 20:15:21 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"
#include "libft.h"
#include "input_code.h"

inline static int64_t	simple_dist(int64_t x1, int64_t y1, int64_t x2,
							int64_t y2);

void	update_ui_slider(t_slider *slider)
{
	t_ui_component	*infos;
	t_ivec2			mouse;
	float			percent;

	if (!slider->infos.displayed)
		return ;
	infos = &slider->infos;
	mouse = get_mouse_pos();
	if (simple_dist(mouse.x, mouse.y, infos->pos.x + slider->cursor_pos_x
			+ infos->size.y / 2, infos->pos.y + infos->size.y / 2)
		<= infos->size.y * infos->size.y || slider->selected)
		slider->hovered = TRUE;
	else
		slider->hovered = FALSE;
	if (!slider->selected)
		return ;
	if (mouse.x < infos->pos.x + infos->size.y / 2)
		mouse.x = infos->pos.x + infos->size.y / 2;
	else if (mouse.x > infos->pos.x + infos->size.x - infos->size.y / 2)
		mouse.x = infos->pos.x + infos->size.x - infos->size.y / 2;
	mouse.x -= infos->pos.x + infos->size.y / 2;
	percent = (float)mouse.x / (float)(infos->size.x - infos->size.y);
	slider->value = slider->min + percent * (slider->max - slider->min);
	slider->cursor_pos_x = mouse.x;
}

void	update_ui_slider_click_begin(t_slider *slider, int mouse_btn)
{
	t_ui_component	*infos;
	t_ivec2			mouse_pos;

	if (!slider->infos.displayed || mouse_btn != MOUSE_LEFT)
		return ;
	infos = &slider->infos;
	mouse_pos = get_mouse_pos();
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

inline static int64_t	simple_dist(int64_t x1, int64_t y1, int64_t x2,
			int64_t y2)
{
	int64_t	dist;
	int64_t	x;
	int64_t	y;

	x = x2 - x1;
	y = y2 - y1;
	dist = x * x + y * y;
	return (dist);
}
