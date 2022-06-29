/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_listeners_handlers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:34:40 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/27 14:35:19 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"

void	handle_f1(t_mlx *app)
{
	if (app->ui.state != KEYBINDS_MENU)
	{
		app->ui.prev_state = app->ui.state;
		app->ui.state = KEYBINDS_MENU;
		return ;
	}
	app->ui.state = app->ui.prev_state;
}
