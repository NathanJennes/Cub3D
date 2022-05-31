/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:42:37 by njennes           #+#    #+#             */
/*   Updated: 2022/05/31 13:06:23 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include "core.h"

int	deserialize_settings(t_settings *settings_out, int fd);

static int			try_open_settings(t_settings *settings_out);
static t_settings	load_default_settings(void);

t_settings	load_settings(void)
{
	t_settings	settings;

	ft_memset(&settings, 0, sizeof (t_settings));
	if (try_open_settings(&settings))
		return (settings);
	printf("Loading default settings\n");
	ft_memset(&settings, 0, sizeof (t_settings));
	return (load_default_settings());
}

static int			try_open_settings(t_settings *settings_out)
{
	int	fd;

	fd = open(APPDATA_DIRECTORY"/settings.txt", O_RDWR, 777);
	if (fd <= 0)
		return (0);
	return (deserialize_settings(settings_out, fd));
}

static t_settings	load_default_settings(void)
{
	t_settings	settings;

	ft_memset(&settings, 0, sizeof (t_settings));
	settings.fov = 90;
	settings.win_w = 960;
	settings.win_h = 540;
	return (settings);
}
