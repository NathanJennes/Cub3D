/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:43:54 by njennes           #+#    #+#             */
/*   Updated: 2022/05/05 15:28:45 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "parsing.h"

void init_hooks();

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

void	init_app(char *file)
{
	init_gc();
	printf("Initial app allocation\n");
	init_map(file);
	init_window("Default Template");
	init_hooks();
	mlx_loop(get_mlx());
}

void init_hooks()
{
	t_mlx	*app;

	app = get_app();
	mlx_mouse_hook(app->win, mouse_hooks, app);
	mlx_hook(app->win, 17, 0, close_app, app);
	mlx_hook(app->win, 2, 1L << 0, key_hooks, app);
	mlx_loop_hook(app->mlx, draw_frame, app);
}
