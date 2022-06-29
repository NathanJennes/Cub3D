/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_padding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:17:09 by njennes           #+#    #+#             */
/*   Updated: 2022/05/20 13:22:16 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

t_ui_component	*uic_padding_up(t_ui_component *comp, int64_t pad)
{
	comp->pad_up = pad;
	return (comp);
}

t_ui_component	*uic_padding_right(t_ui_component *comp, int64_t pad)
{
	comp->pad_right = pad;
	return (comp);
}

t_ui_component	*uic_padding_down(t_ui_component *comp, int64_t pad)
{
	comp->pad_down = pad;
	return (comp);
}

t_ui_component	*uic_padding_left(t_ui_component *comp, int64_t pad)
{
	comp->pad_left = pad;
	return (comp);
}

t_ui_component	*uic_padding(t_ui_component *comp, t_ivec2 td, t_ivec2 lr)
{
	comp->pad_up = td.x;
	comp->pad_right = lr.y;
	comp->pad_down = td.y;
	comp->pad_left = lr.x;
	return (comp);
}
