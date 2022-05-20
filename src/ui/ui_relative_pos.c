/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_relative_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:22:37 by njennes           #+#    #+#             */
/*   Updated: 2022/05/20 13:34:24 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

t_ui_component	*uic_below(t_ui_component *comp, t_ui_component *other)
{
	comp->pos.x = other->pos.x + other->size.x / 2 - comp->size.x / 2;
	comp->pos.y = other->pos.y + other->size.y + ft_maxi(comp->pad_up, other->pad_down);
	return (comp);
}

t_ui_component	*uic_above(t_ui_component *comp, t_ui_component *other)
{
	comp->pos.x = other->pos.x + other->size.x / 2 - comp->size.x / 2;
	comp->pos.y = other->pos.y - comp->size.y - ft_maxi(comp->pad_down, other->pad_up);
	return (comp);
}

t_ui_component	*uic_side_left(t_ui_component *comp, t_ui_component *other)
{
	comp->pos.x = other->pos.x - comp->size.x - ft_maxi(comp->pad_right, other->pad_left);
	comp->pos.y = other->pos.y + other->size.y / 2 - comp->size.y / 2;
	return (comp);
}

t_ui_component	*uic_side_right(t_ui_component *comp, t_ui_component *other)
{
	comp->pos.x = other->pos.x + other->size.x + ft_maxi(comp->pad_left, other->pad_right);
	comp->pos.y = other->pos.y + other->size.y / 2 - comp->size.y / 2;
	return (comp);
}
