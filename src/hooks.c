/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:57:26 by cybattis          #+#    #+#             */
/*   Updated: 2022/04/20 21:21:52 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "core.h"
#include "input_code.h"

int	mouse_hooks(int mousecode, int x, int y)
{
	(void)x;
	(void)y;
	if (mousecode)
		dprintf(STDERR_FILENO, "Mouse: %d\n", mousecode);
	return (0);
}

int	key_hooks(int keycode, t_mlx *app)
{
	if (keycode == KEY_LEFT || keycode == KEY_UP || keycode == KEY_RIGHT
		|| keycode == KEY_DOWN)
		dprintf(STDERR_FILENO, "Arrow: %d\n", keycode);
	else if (keycode == KEY_ESC)
		close_app(app);
	else
		dprintf(STDERR_FILENO, "%d\n", keycode);
	return (0);
}
