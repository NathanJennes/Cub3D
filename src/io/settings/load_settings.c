/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:42:37 by njennes           #+#    #+#             */
/*   Updated: 2022/06/26 17:22:59 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core.h>

t_settings	load_settings(void)
{
	t_settings	settings;

	ft_memset(&settings, 0, sizeof (t_settings));
	settings.fov = 90;
	settings.win_w = 960;
	settings.win_h = 540;
	settings.desired_win_w = 960;
	settings.desired_win_h = 540;
	settings.halfw_w = 960 / 2;
	settings.halfw_h = 540 / 2;
	settings.cam_sensitivity = 0.5;
	settings.last_save = "";
	return (settings);
}
