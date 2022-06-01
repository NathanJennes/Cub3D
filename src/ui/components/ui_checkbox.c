/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_checkbox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:35:53 by njennes           #+#    #+#             */
/*   Updated: 2022/06/01 12:51:10 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "ui.h"

t_checkbox	create_checkbox(char *texture_path, t_ivec2 pos,
	int (*event_checked)(struct s_checkbox *checkbox),
	int (*event_unchecked)(struct s_checkbox *checkbox))
{
	t_checkbox	checkbox;

	ft_memset(&checkbox, 0, sizeof (t_checkbox));
	checkbox.infos.pos = pos;
	if (texture_path)
		checkbox.tex_id = load_texture(texture_path);
	else
		checkbox.tex_id = INVALID_TEXTURE;
	checkbox.infos.size = get_texture_size(checkbox.tex_id);
	checkbox.infos.displayed = TRUE;
	checkbox.event_checked = event_checked;
	checkbox.event_unchecked = event_unchecked;
	checkbox.hovered = FALSE;
	checkbox.is_clickable = TRUE;
	checkbox.checked = FALSE;
	return (checkbox);
}

void	render_ui_checkbox(t_checkbox *checkbox)
{
	t_ui_component	*infos;

	if (!checkbox->infos.displayed)
		return ;
	infos = &checkbox->infos;
	if (!checkbox->is_clickable || checkbox->checked)
		render_ui_texture_inverse_grayscale(checkbox->tex_id,
			infos->pos.x, infos->pos.y);
	else if (checkbox->hovered)
		render_ui_texture_grayscale(checkbox->tex_id, infos->pos.x, infos->pos.y);
	else
		render_ui_texture(checkbox->tex_id, infos->pos.x, infos->pos.y);
}

