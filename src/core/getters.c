/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:19:50 by njennes           #+#    #+#             */
/*   Updated: 2022/06/15 18:36:55 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_mlx	*get_app(void)
{
	static t_mlx	app = {0};

	return (&app);
}

t_frame	*get_frame(void)
{
	t_mlx	*app;

	app = get_app();
	return (&app->frame);
}

t_map_info	*get_map_infos(void)
{
	t_mlx	*app;

	app = get_app();
	return (&app->gamestate.map);
}

t_player	*get_player(void)
{
	t_mlx	*app;

	app = get_app();
	return (&app->gamestate.player);
}

void	*get_mlx(void)
{
	t_mlx	*app;

	app = get_app();
	return (app->mlx);
}
