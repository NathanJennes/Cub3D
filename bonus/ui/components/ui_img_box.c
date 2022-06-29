/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_img_box.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:06:46 by njennes           #+#    #+#             */
/*   Updated: 2022/05/18 15:11:56 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "render.h"

t_img_box	create_img_box(char *texture_path, t_ivec2 pos)
{
	t_img_box	box;

	ft_memset(&box, 0, sizeof (t_img_box));
	box.infos.pos = pos;
	box.infos.displayed = TRUE;
	box.tex_id = load_texture(texture_path);
	box.infos.size = get_texture_size(box.tex_id);
	return (box);
}

void	render_ui_img_box(t_img_box *box)
{
	if (!box->infos.displayed)
		return ;
	render_ui_texture(box->tex_id, box->infos.pos.x, box->infos.pos.y);
}
