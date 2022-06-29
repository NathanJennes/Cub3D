/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_centering.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:08:57 by njennes           #+#    #+#             */
/*   Updated: 2022/05/20 13:16:13 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

t_ui_component	*uic_center_win_w(t_ui_component *comp)
{
	t_settings	*settings;

	settings = get_settings();
	comp->pos.x = settings->win_w / 2 - comp->size.x / 2;
	return (comp);
}

t_ui_component	*uic_center_win_h(t_ui_component *comp)
{
	t_settings	*settings;

	settings = get_settings();
	comp->pos.y = settings->win_h / 2 - comp->size.y / 2;
	return (comp);
}

t_ui_component	*uic_center_win(t_ui_component *comp)
{
	return (uic_center_win_w(uic_center_win_h(comp)));
}
