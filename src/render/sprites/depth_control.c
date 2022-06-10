/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:40:20 by njennes           #+#    #+#             */
/*   Updated: 2022/06/10 17:41:57 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

double	get_depth_at(int64_t i)
{
	t_renderer	*renderer;

	renderer = &get_app()->renderer;
	return (renderer->depth_buffer[i]);
}

void	set_depth_at(int64_t i, double distance)
{
	t_renderer	*renderer;

	renderer = &get_app()->renderer;
	renderer->depth_buffer[i] = distance;
}
