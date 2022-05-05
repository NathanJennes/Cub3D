/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:50:41 by njennes           #+#    #+#             */
/*   Updated: 2022/05/05 16:38:18 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	show_slider(t_slider *slider)
{
	t_vec2	btn2_pos;
	t_vec2	line_start;
	t_vec2	line_end;
	int		cursor_color;
	float	cursor_val;

	btn2_pos = slider->pos;
	btn2_pos.x += SLIDER_BTN2_XO;
	line_start = vec2(slider->pos.x + SLIDER_BTN_W + SLIDER_PAD,
			slider->pos.y + SLIDER_H / 2);
	line_end = vec2(slider->pos.x + SLIDER_BTN_W + SLIDER_PAD + SLIDER_W,
			slider->pos.y + SLIDER_H / 2);
	render_rect(slider->pos, (t_vec2){25, 25}, create_trgb(0, 150, 51, 51));
	render_rect(btn2_pos, (t_vec2){25, 25}, create_trgb(0, 51, 51, 150));
	render_line(line_start, line_end, create_trgb(0, 150, 51, 51),
		create_trgb(0, 51, 51, 150));
	cursor_val = (slider->value - slider->min) / (slider->max - slider->min);
	line_start = vec2(
		slider->pos.x + SLIDER_BTN_W + SLIDER_PAD + SLIDER_W * cursor_val,
		slider->pos.y);
	line_end = vec2(
		slider->pos.x + SLIDER_BTN_W + SLIDER_PAD + SLIDER_W * cursor_val,
		slider->pos.y + SLIDER_H);
	cursor_color = color_lerp(create_trgb(0, 150, 51, 51),
		create_trgb(0, 51, 51, 150), cursor_val);
	render_line(line_start, line_end, cursor_color, cursor_color);
}

void	update_slider(t_slider *slider, int mx, int my)
{
	if (mx > slider->pos.x && mx < slider->pos.x + SLIDER_BTN_W
		&& my > slider->pos.y && my < slider->pos.y + SLIDER_H)
		slider->value -= slider->increment_size;
	if (mx > slider->pos.x + SLIDER_BTN2_XO
		&& mx < slider->pos.x + SLIDER_BTN2_XO + SLIDER_BTN_W
		&& my > slider->pos.y && my < slider->pos.y + SLIDER_H)
		slider->value += slider->increment_size;
	if (slider->value < slider->min)
		slider->value = slider->min;
	if (slider->value > slider->max)
		slider->value = slider->max;
}
