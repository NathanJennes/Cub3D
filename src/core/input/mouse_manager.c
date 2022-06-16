/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyril <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:09:40 by njennes           #+#    #+#             */
/*   Updated: 2022/06/14 09:57:17 by Cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "input_code.h"

void		mouse_click_begin(int button);
void		mouse_click_end(int button);
void		mouse_wheel_up(void);
void		mouse_wheel_down(void);

inline static int	handle_scroll_wheel(int button);

int	mouse_up_callback(int button, int x, int y, void *unused)
{
	t_mlx	*app;

	(void)unused;
	cub_update_mouse_pos(x, y);
	app = get_app();
	if (app->mouse.buttons[button])
	{
		app->mouse.buttons[button] = FALSE;
		mouse_click_end(button);
		return (0);
	}
	app->mouse.buttons[button] = FALSE;
	return (0);
}

int	mouse_down_callback(int button, int x, int y, void *unused)
{
	t_mlx	*app;

	(void)unused;
	cub_update_mouse_pos(x, y);
	if (handle_scroll_wheel(button))
		return (0);
	app = get_app();
	if (!app->mouse.buttons[button])
	{
		app->mouse.buttons[button] = TRUE;
		mouse_click_begin(button);
		return (0);
	}
	app->mouse.buttons[button] = TRUE;
	return (0);
}

int	mouse_move_hooks(int x, int y, void *unused)
{
	(void)unused;
	cub_update_mouse_pos(x, y);
	update_ui();
	return (0);
}

t_bool	is_mouse_down(int button)
{
	return (get_app()->mouse.buttons[button]);
}

inline static int	handle_scroll_wheel(int button)
{
	if (button == MOUSE_WHEELUP)
	{
		mouse_wheel_up();
		return (1);
	}
	else if (button == MOUSE_WHEELDOWN)
	{
		mouse_wheel_down();
		return (1);
	}
	return (0);
}
