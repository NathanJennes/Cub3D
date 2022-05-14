/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:48:00 by njennes           #+#    #+#             */
/*   Updated: 2022/05/09 22:48:43 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "core.h"
#include "texture.h"

t_xpm_file	load_xpm(char *path)
{
	t_xpm_file	file;

	file.handle = mlx_xpm_file_to_image(get_mlx(), path,
			&file.width, &file.height);
	if (!file.handle)
		return (file);
	file.data = (uint8_t *)mlx_get_data_addr(file.handle, &file.bpp,
			&file.line_size, &file.endian);
	return (file);
}
