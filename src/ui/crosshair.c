/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:46:25 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/27 14:47:10 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"
#include "render.h"

void	render_crosshair(void)
{
	t_texture	*crosshair;

	if (get_app()->state != IN_GAME)
		return ;
	crosshair = get_texture_from_id(get_ui()->tx_crosshair);
	render_ui_texture(get_ui()->tx_crosshair,
		get_settings()->halfw_w - crosshair->width / 2,
		get_settings()->halfw_h - crosshair->height / 2);
}
