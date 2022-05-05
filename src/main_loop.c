/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:44:35 by njennes           #+#    #+#             */
/*   Updated: 2022/05/05 16:28:11 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int	main_loop()
{
	t_mlx	*app;

	app = get_app();
	clear_screen(BKGD_COLOR);
	render_mmap(app->map_scale_slider.value);
	show_slider(&app->map_scale_slider);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	return (0);
}
