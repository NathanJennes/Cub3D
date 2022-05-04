/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:51:10 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/04 19:09:58 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "core.h"
#include "leaky.h"

void	init_window(t_mlx *app, char *win_name)
{
	app->mlx = mlx_init();
	if (!app->mlx)
		error_close_app(app);
	app->win = mlx_new_window(app->mlx, WIN_W, WIN_H, win_name);
	if (!app->win)
		error_close_app(app);
	app->frame.img = mlx_new_image(app->mlx, WIN_W, WIN_H);
	if (!app->frame.img)
		error_close_app(app);
	app->frame.addr = mlx_get_data_addr(app->frame.img, &app->frame.bits_pp,
			&app->frame.line_length, &app->frame.endian);
	if (!app->frame.addr)
		error_close_app(app);
}

int	close_app(t_mlx *app)
{
	check_leaky_errors();
	mlx_destroy_image(app->mlx, app->frame.img);
	mlx_destroy_window(app->mlx, app->win);
	printf("Footprint before free: %lu\n", gc_getfootprint());
	gc_print_status();
	gc_free(app);
	printf("Footprint after free: %lu\n", gc_getfootprint());
	gc_print_status();
	gc_clean();
	exit(EXIT_SUCCESS);
}

void	error_close_app(t_mlx *app)
{
	check_leaky_errors();
	if (app->mlx && app->frame.img)
		mlx_destroy_image(app->mlx, app->frame.img);
	if (app->mlx && app->win)
		mlx_destroy_window(app->mlx, app->win);
	gc_clean();
	printf("Error\n");
	exit(EXIT_FAILURE);
}
void	check_leaky_errors(void)
{
	size_t	i;

	if (gc_strarray_size((char **) gc_get_errors()) == 0)
		printf("Leaky has no errors\n");
	else
		printf("Leaky has errors\n");
	i = 0;
	while (i < gc_strarray_size((char **) gc_get_errors()))
	{
		printf("Error[%lu]: %s\n", i, gc_get_errors()[i]);
		i++;
	}
}
