/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:48:00 by njennes           #+#    #+#             */
/*   Updated: 2022/05/16 18:50:32 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "core.h"
#include "texture.h"

int	load_xpm(t_xpm_file *xpm_out, char *path)
{
	t_xpm_file	file;

	ft_memset(&file, 0, sizeof(t_xpm_file));
	file.handle = mlx_xpm_file_to_image(get_mlx(), path,
			&file.width, &file.height);
	if (!file.handle)
		return (0);
	file.data = (uint8_t *)mlx_get_data_addr(file.handle, &file.bpp,
			&file.line_size, &file.endian);
	*xpm_out = file;
	return (1);
}
