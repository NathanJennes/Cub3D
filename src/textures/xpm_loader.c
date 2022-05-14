/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:48:00 by njennes           #+#    #+#             */
/*   Updated: 2022/05/14 15:56:33 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "core.h"
#include "texture.h"
#include "leaky.h"

t_xpm_file	load_xpm(char *path)
{
	t_xpm_file	file;

	gc_memset(&file, 0, sizeof(t_xpm_file));
	file.handle = mlx_xpm_file_to_image(get_mlx(), path,
			&file.width, &file.height);
	if (!file.handle)
	{
		cub_set_error(RESSOURCE_NOT_FOUND);
		return (file);
	}
	file.data = (uint8_t *)mlx_get_data_addr(file.handle, &file.bpp,
			&file.line_size, &file.endian);
	return (file);
}
