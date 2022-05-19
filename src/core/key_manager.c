/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:07:56 by njennes           #+#    #+#             */
/*   Updated: 2022/05/19 15:44:58 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int	key_pressed_listener(int keycode);

int	key_up_callback(int keycode)
{
	t_mlx	*app;

	app = get_app();
	if (keycode < 0 || keycode >= MAX_KEYCODE)
		return (0);
	app->keys[keycode] = FALSE;
	return (0);
}

int	key_down_callback(int keycode)
{
	t_mlx	*app;

	app = get_app();
	if (keycode < 0 || keycode >= MAX_KEYCODE)
		return (0);
	if (!app->keys[keycode])
	{
		app->keys[keycode] = TRUE;
		key_pressed_listener(keycode);
		return (0);
	}
	app->keys[keycode] = TRUE;
	return (0);
}

t_bool	is_key_down(int keycode)
{
	return (get_app()->keys[keycode]);
}
