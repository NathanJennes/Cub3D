/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savegame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:44:59 by njennes           #+#    #+#             */
/*   Updated: 2022/06/20 16:51:27 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/stat.h>
#include "bool.h"
#include "leaky.h"
#include "core.h"
#include "render.h"

void		serialize_game(int fd);
int			deserialize_save(t_gamestate *save_out, int fd, char *filename);

inline static int	open_save_file(char *save_name, int truncate);
inline static void	create_appdata_directory(void);

int	save_game(char *save_name)
{
	int		fd;
	char	*new_name;
	char	*dot;
	size_t	new_size;

	dot = ft_strrchr(save_name, '.');
	if (!dot)
		return (0);
	new_size = ft_strlen(save_name) - ft_strlen(dot);
	new_name = gc_substr(save_name, 0, new_size);
	new_name = gc_strjoin(new_name, ".save", FREE_FIRST);
	fd = open_save_file(new_name, TRUE);
	gc_free(new_name);
	if (fd == -1)
		return (0);
	serialize_game(fd);
	close(fd);
	reload_saves();
	return (1);
}

int	load_save(t_gamestate *save_out, char *save_name)
{
	t_gamestate	save;
	int			fd;

	ft_memset(&save, 0, sizeof (t_gamestate));
	fd = open_save_file(save_name, FALSE);
	if (fd == -1)
		return (0);
	if (!deserialize_save(&save, fd, save_name))
	{
		gc_strarray_free(save.map.map_raw);
		gc_free2d((void **)save.map.map, save.map.height);
		return (0);
	}
	save.name = gc_strdup(save_name);
	close(fd);
	*save_out = save;
	return (1);
}

void	free_save(t_gamestate *save)
{
	gc_free2d((void **) save->map.map, save->map.height);
	gc_free(save->name);
	free_lights(save);
}

inline static int	open_save_file(char *save_name, int truncate)
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
		fd = open(save_file, O_RDWR, 0777);
	gc_free(save_file);
	return (fd);
}

inline static void	create_appdata_directory(void)
{
	struct stat	dir;

	ft_memset(&dir, 0, sizeof (struct stat));
	if (stat(APPDATA_DIRECTORY, &dir) == -1)
		mkdir(APPDATA_DIRECTORY, 0777);
}
