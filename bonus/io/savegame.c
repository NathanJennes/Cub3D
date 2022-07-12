/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savegame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:44:59 by njennes           #+#    #+#             */
/*   Updated: 2022/07/12 17:18:14 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/stat.h>
#include "bool.h"
#include "core.h"
#include "render.h"
#include "libft.h"

void				serialize_game(int fd);
int					deserialize_save(t_gamestate *save_out, int fd,
						char *filename);
inline static int			open_save_file(char *save_name, int truncate);
inline static void		create_appdata_directory(void);
inline static char		*return_save_name(char *new_name);

char	*save_game(char *save_name)
{
	int		fd;
	char	*new_name;
	char	*dot;
	size_t	new_size;

	dot = ft_strrchr(save_name, '.');
	if (!dot)
		return (NULL);
	new_size = ft_strlen(save_name) - ft_strlen(dot);
	new_name = gc_substr(save_name, 0, new_size);
	new_name = gc_strjoin(new_name, ".save", FREE_FIRST);
	fd = open_save_file(new_name, TRUE);
	if (fd == -1)
		return (NULL);
	serialize_game(fd);
	close(fd);
	reload_saves();
	return (return_save_name(new_name));
}

inline static char	*return_save_name(char *new_name)
{
	size_t	i;
	t_mlx	*app;

	app = get_app();
	i = 0;
	while (i < get_app()->savegames_count)
	{
		if (ft_strcmp(app->savegames[i].name, new_name) == 0)
		{
			gc_free(new_name);
			return (app->savegames[i].name);
		}
		i++;
	}
	gc_free(new_name);
	return (NULL);
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

inline static int	open_save_file(char *save_name, int truncate)
{
	int		fd;
	char	*save_file;

	create_appdata_directory();
	save_file = gc_strdup(APPDATA_DIRECTORY);
	save_file = gc_strappend(save_file, '/');
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
