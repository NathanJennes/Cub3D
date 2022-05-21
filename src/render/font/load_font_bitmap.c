/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_font_bitmap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 13:13:29 by njennes           #+#    #+#             */
/*   Updated: 2022/05/21 13:26:11 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "mlx.h"
#include "core.h"
#include "leaky.h"

t_font_bitmap	load_bitmap_font(char *path)
{
	t_font_bitmap	font;
	void			*img;
	char			*data;

	ft_memset(&font, 0, sizeof (t_font_bitmap));
	img = mlx_png_file_to_image(get_mlx(), path, &font.width, &font.height);
	if (!img)
	{
		printf("Couldn't load font %s\n", path);
		return (font);
	}
	data = mlx_get_data_addr(img, &font.bpp, &font.line_size, &font.endian);
	font.data = (uint8_t *)gc_calloc(font.width * font.height, font.bpp / 8);
	gc_memmove(font.data, data, font.width * font.height * font.bpp / 8);
	mlx_destroy_image(get_mlx(), img);
	return (font);
}

void	unload_bitmap_font(t_font_bitmap *font)
{
	gc_free(font->data);
}
