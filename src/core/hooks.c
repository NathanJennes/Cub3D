/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:57:26 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/19 15:44:00 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "core.h"
#include "input_code.h"
#include "ui.h"

int	mouse_hooks(int mousecode, int x, int y)
{
	(void)x;
	(void)y;
	if (mousecode)
		dprintf(STDERR_FILENO, "Mouse: %d\n", mousecode);
	update_ui(TRUE);
	return (0);
}

int	mouse_move_hooks(int x, int y, void *param)
{
	(void)param;
	cub_update_mouse_pos(x, y);
	update_ui(FALSE);
	return (0);
}
