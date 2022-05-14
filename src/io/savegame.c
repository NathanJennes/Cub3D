/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savegame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:44:59 by njennes           #+#    #+#             */
/*   Updated: 2022/05/14 19:26:19 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include "leaky.h"
#include "core.h"

void		serialize_game(int fd);

static int	open_save_file(char *save_name, int truncate);
static void	create_appdata_directory(void);

void	save_game(char *save_name)
{
	int	fd;

	fd = open_save_file(save_name, TRUE);
	if (fd == -1)
		return ;
	serialize_game(fd);
}

static int	open_save_file(char *save_name, int truncate)
{
	int		fd;
	char	*save_file;

	create_appdata_directory();
	save_file = gc_strdup(APPDATA_DIRECTORY);
	save_file = gc_strappend(save_file, '/', LK_TRUE);
	save_file = gc_strjoin(save_file, save_name, FREE_FIRST);
	if (truncate)
		fd = open(save_file, O_CREAT | O_RDWR | O_TRUNC, 0777);
	else
		fd = open(save_file, O_CREAT | O_RDWR, 0777);
	if (fd == -1)
		cub_set_error(SAVE_ERROR);
	gc_free(save_file);
	return (fd);
}

static void	create_appdata_directory(void)
{
	struct stat dir;

	ft_memset(&dir, 0, sizeof (struct stat));
	if(stat(APPDATA_DIRECTORY, &dir) == -1)
		mkdir(APPDATA_DIRECTORY, 0777);
}
