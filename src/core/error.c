/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 15:40:07 by njennes           #+#    #+#             */
/*   Updated: 2022/05/14 15:48:52 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "error.h"

void	cub_set_error(t_error error)
{
	t_mlx	*app;

	app = get_app();
	app->last_error = error;
}

void	cub_unset_error(void)
{
	t_mlx	*app;

	app = get_app();
	app->last_error = NONE;
}

int	cub_has_error(void)
{
	t_mlx	*app;

	app = get_app();
	if (app->last_error == NONE)
		return (0);
	return (1);
}

int	cub_get_error(void)
{
	t_mlx	*app;

	app = get_app();
	return (app->last_error);
}

int	cub_consume_error(void)
{
	t_mlx	*app;
	t_error	error;

	app = get_app();
	error = app->last_error;
	cub_unset_error();
	return (error);
}
