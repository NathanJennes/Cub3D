/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:51:53 by njennes           #+#    #+#             */
/*   Updated: 2022/07/12 17:18:14 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include <sys/stat.h>
#include "core.h"

inline static void	save_player(t_settings *settings, int fd);
inline static void	save_win(t_settings *settings, int fd);

inline static int		open_settings_file(char *save_name);
inline static void	create_directory_appdata(void);

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
	dprintf(fd, "LAST_SAVE %s\n", settings->last_save);
}

inline static void	save_player(t_settings *settings, int fd)
{
	dprintf(fd, "FOV ");
	dprintf(fd, "%d\n", settings->fov);
	dprintf(fd, "SENS ");
	dprintf(fd, "%d.%d\n", (int)settings->cam_sensitivity,
		(int)((settings->cam_sensitivity
				- (double)((int)settings->cam_sensitivity)) * 100));
}

inline static void	save_win(t_settings *settings, int fd)
{
	dprintf(fd, "WIN ");
	dprintf(fd, "%d %d\n", settings->desired_win_w, settings->desired_win_h);
}

inline static int	open_settings_file(char *save_name)
{
	int		fd;
	char	*save_file;

	create_directory_appdata();
	save_file = gc_strdup(APPDATA_DIRECTORY);
	save_file = gc_strappend(save_file, '/');
	save_file = gc_strjoin(save_file, save_name, FREE_FIRST);
	fd = open(save_file, O_CREAT | O_RDWR | O_TRUNC, 0777);
	gc_free(save_file);
	return (fd);
}

inline static void	create_directory_appdata(void)
{
	struct stat	dir;

	ft_memset(&dir, 0, sizeof (struct stat));
	if (stat(APPDATA_DIRECTORY, &dir) == -1)
		mkdir(APPDATA_DIRECTORY, 0777);
}
