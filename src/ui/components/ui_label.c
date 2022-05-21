/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_label.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:30:08 by njennes           #+#    #+#             */
/*   Updated: 2022/05/18 15:45:31 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "render.h"

t_label	create_label(t_ivec2 pos, char *text)
{
	t_label	label;

	ft_memset(&label, 0, sizeof (t_label));
	label.infos.pos = pos;
	label.infos.size = ivec2(10, 10);
	label.infos.displayed = TRUE;
	label.text = text;
	return (label);
}

void	render_label(t_label *label)
{
	if (!label->infos.displayed)
		return ;
	mlx_render_text(label->text, label->infos.pos);
}
