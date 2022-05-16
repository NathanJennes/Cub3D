/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:42:46 by njennes           #+#    #+#             */
/*   Updated: 2022/05/16 21:04:10 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "render.h"

void	render_ui_label(t_label *label)
{
	render_ui_texture(label->tex_id, label->pos.x, label->pos.y);
}

void	render_ui_img_box(t_img_box *img_box)
{
	if (img_box->displayed)
		render_ui_texture(img_box->tex_id, img_box->pos.x, img_box->pos.y);
}

void	render_ui_button(t_button *button)
{
	if (!button->displayed)
		return ;
	if (button->clicked)
		render_ui_texture(button->tex_id_select, button->pos.x, button->pos.y);
	else if (button->hovered)
		render_ui_texture(button->tex_id_hover, button->pos.x, button->pos.y);
	else
		render_ui_texture(button->tex_id, button->pos.x, button->pos.y);
}
