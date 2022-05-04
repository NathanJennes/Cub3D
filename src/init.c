/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:43:54 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 18:25:36 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "parsing.h"
#include "leaky.h"

void init_hooks(t_mlx *app);

int	is_legal_file(int argc, char **argv)
{
	char	*extension;

	if (argc != 2)
		return (0);
	extension = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]));
	if (!extension)
		return (0);
	if (extension[4])
		return (0);
	return (1);
}

t_mlx	*init_app(char *file)
{
	t_mlx	*app;

	init_gc();
	printf("Initial app allocation\n");
	app = gc_calloc(1, sizeof(t_mlx));
	post_init_gc(app);
	gc_object_start(app);
	init_map(app, file);
	init_window(app, "Default Template");
	gc_object_end();
	init_hooks(app);
	mlx_loop(app->mlx);
	return (app);
}

void init_hooks(t_mlx *app)
{
	mlx_mouse_hook(app->win, mouse_hooks, app);
	mlx_hook(app->win, 17, 0, close_app, app);
	mlx_hook(app->win, 2, 1L << 0, key_hooks, app);
	mlx_loop_hook(app->mlx, draw_frame, app);
}
