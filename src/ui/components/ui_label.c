/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_label.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:30:08 by njennes           #+#    #+#             */
/*   Updated: 2022/05/31 17:35:51 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "render.h"

t_label	create_label(t_ivec2 pos, char *text, t_ivec2 size, int font_size)
{
	t_label	label;

	ft_memset(&label, 0, sizeof (t_label));
	label.infos.pos = pos;
	label.infos.size = size;
	label.infos.displayed = TRUE;
	label.text = text;
	label.tex_id = new_texture(size.x, size.y);
	render_text_tex(label.text, DEFAULT_FONT,
		text_center(label.text, DEFAULT_FONT, font_size,
			ivec2(size.x / 2, size.y / 2)),
		ivec2(font_size, label.tex_id));
	finish_new_texture(label.tex_id);
	return (label);
}

void	render_ui_label(t_label *label)
{
	if (!label->infos.displayed)
		return ;
	render_ui_texture(label->tex_id, label->infos.pos.x, label->infos.pos.y);
}

void	update_ui_label_text(t_label *label, char *text)
{
	label->text = text;
	clear_texture(trgb(255, 0, 0, 0), label->tex_id);
	render_text_tex(label->text, DEFAULT_FONT,
		text_center(label->text, DEFAULT_FONT, label->font_size,
			ivec2(label->infos.size.x / 2, label->infos.size.y / 2)),
		ivec2(label->font_size, label->tex_id));
}
