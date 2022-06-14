/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:51:53 by njennes           #+#    #+#             */
/*   Updated: 2022/06/01 15:19:28 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include <sys/stat.h>
#include "core.h"
#include "leaky.h"

static void	save_player(t_settings *settings, int fd);
static void	save_win(t_settings *settings, int fd);

static int	open_settings_file(char *save_name);
static void	create_appdata_directory(void);

void	save_settings(t_settings *settings)
{
	int	fd;

	fd = open_settings_file("settings.txt");
	if (fd <= 0)
	{
		printf("Could not save the settings\n");
		return ;
	}
	save_player(settings, fd);
	save_win(settings, fd);
}

static void	save_player(t_settings *settings, int fd)
{
	dprintf(fd, "FOV ");
	dprintf(fd, "%d\n", settings->fov);
	dprintf(fd, "SENS ");
	dprintf(fd, "%d.%d\n", (int)settings->cam_sensitivity,
		(int)((settings->cam_sensitivity
				- (double)((int)settings->cam_sensitivity)) * 100));
}

static void	save_win(t_settings *settings, int fd)
{
	dprintf(fd, "WIN ");
	dprintf(fd, "%d %d\n", settings->desired_win_w, settings->desired_win_h);
}

static int	open_settings_file(char *save_name)
{
	int		fd;
	char	*save_file;

	create_appdata_directory();
	save_file = gc_strdup(APPDATA_DIRECTORY);
	save_file = gc_strappend(save_file, '/', LK_TRUE);
	save_file = gc_strjoin(save_file, save_name, FREE_FIRST);
	fd = open(save_file, O_CREAT | O_RDWR | O_TRUNC, 0777);
	gc_free(save_file);
	return (fd);
}

static void	create_appdata_directory(void)
{
	struct stat	dir;

	ft_memset(&dir, 0, sizeof (struct stat));
	if (stat(APPDATA_DIRECTORY, &dir) == -1)
		mkdir(APPDATA_DIRECTORY, 0777);
}
