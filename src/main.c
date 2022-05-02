/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 18:35:28 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/02 13:16:35 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "core.h"
#include "leaky.h"

int	main(void)
{
	t_mlx	*app;

	app = gc_calloc(1, sizeof(t_mlx));
	init_window(app, "Default Template");
	mlx_mouse_hook(app->win, mouse_hooks, app);
	mlx_hook(app->win, 17, 0, close_app, app);
	mlx_hook(app->win, 2, 1L << 0, key_hooks, app);
	mlx_loop_hook(app->mlx, draw_frame, app);
	mlx_loop(app->mlx);
	return (0);
}
