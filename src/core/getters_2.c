/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:19:50 by njennes           #+#    #+#             */
/*   Updated: 2022/05/19 19:30:44 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_ui	*get_ui(void)
NOPROF
{
	t_mlx	*app;

	app = get_app();
	return (&app->ui);
}

t_settings	*get_settings(void)
NOPROF
{
	t_mlx	*app;

	app = get_app();
	return (&app->settings);
}

t_math	*get_math(void)
NOPROF
{
	t_mlx	*app;

	app = get_app();
	return (&app->pc);
}
