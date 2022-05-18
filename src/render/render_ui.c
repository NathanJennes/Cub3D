/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:42:46 by njennes           #+#    #+#             */
/*   Updated: 2022/05/16 22:12:11 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "render.h"

void	render_ui_label(t_label *label)
{
	render_ui_texture(label->tex_id, label->infos.pos.x, label->infos.pos.y);
}

void	render_ui_img_box(t_img_box *img_box)
{
	if (img_box->infos.displayed)
		render_ui_texture(img_box->tex_id, img_box->infos.pos.x, img_box->infos.pos.y);
}

void	render_ui_button(t_button *button)
{
	if (!button->infos.displayed)
		return ;
	if (button->clicked)
		render_ui_texture_grayscale(button->tex_id, button->infos.pos.x, button->infos.pos.y);
	else if (button->hovered)
		render_ui_texture_inversed(button->tex_id, button->infos.pos.x, button->infos.pos.y);
	else
		render_ui_texture(button->tex_id, button->infos.pos.x, button->infos.pos.y);
}
