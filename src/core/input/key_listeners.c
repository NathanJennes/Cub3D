/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_listeners.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:42:50 by njennes           #+#    #+#             */
/*   Updated: 2022/06/29 15:52:41 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "input_code.h"

int	key_pressed_listener(int keycode)
{
	if (keycode == KEY_BACKSPACE)
		close_app();
	return (0);
}
