/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_button.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 22:30:28 by njennes           #+#    #+#             */
/*   Updated: 2022/05/19 18:44:17 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "render.h"

//TODO: refactor to uniformize ui creation prototypes
t_button	create_button(int64_t tex_id,
		t_ivec2 pos,
		int (*event)(struct s_button *button))
{
	t_button	button;

	ft_memset(&button, 0, sizeof (t_button));
	button.infos.pos = pos;
	button.infos.size = get_texture_size(tex_id);
	button.infos.displayed = TRUE;
	button.tex_id = tex_id;
	button.event = event;
	button.hovered = FALSE;
	button.clicked = FALSE;
	button.is_clickable = TRUE;
	return (button);
}

void	render_ui_button(t_button *button)
{
	t_ui_component	*infos;

	if (!button->infos.displayed)
		return ;
	infos = &button->infos;
	if (button->clicked)
		render_ui_texture_inverse_grayscale(button->tex_id, infos->pos.x, infos->pos.y);
	else if (button->hovered)
		render_ui_texture_grayscale(button->tex_id, infos->pos.x, infos->pos.y);
	else
		render_ui_texture(button->tex_id, infos->pos.x, infos->pos.y);
}
