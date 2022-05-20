/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:19:50 by njennes           #+#    #+#             */
/*   Updated: 2022/05/12 22:39:10 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_ui	*get_ui(void)
{
	t_mlx	*app;

	app = get_app();
	return (&app->ui);
}

t_settings	*get_settings(void)
{
	t_mlx	*app;

	app = get_app();
	return (&app->gamestate.settings);
}
