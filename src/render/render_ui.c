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
	render_ui_texture(label->tex_id, label->position.x, label->position.y);
}

void	render_ui_img_box(t_img_box *img_box)
{
	if (img_box->displayed)
		render_ui_texture(img_box->tex_id, img_box->position.x, img_box->position.y);
}

void	render_ui_button(t_button *button)
{
	if (!button->displayed)
		return ;
	if (button->clicked)
		render_ui_texture(button->tex_id_select, button->position.x, button->position.y);
	else if (button->hovered)
		render_ui_texture(button->tex_id_hover, button->position.x, button->position.y);
	else
		render_ui_texture(button->tex_id, button->position.x, button->position.y);
}
