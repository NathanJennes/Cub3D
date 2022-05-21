/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:33:19 by njennes           #+#    #+#             */
/*   Updated: 2022/05/21 15:28:48 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "libft.h"

void	render_font(void)
{
	t_font_meta	font;

	ft_memset(&font, 0, sizeof (t_font_meta));
	if (!load_font_meta(&font, "assets/ui/cube-export/test_font_2.fnt"))
	{
		printf("Can't create font\n");
		return ;
	}
	font.bitmap = load_bitmap_font("assets/ui/cube-export/test_font_2.png");
	if (!font.bitmap.data)
	{
		printf("Failed to load font bitmap\n");
		return ;
	}
	printf("font loaded\n");
	printf("Name: %s\nSize: %d\n\n", font.name, font.font_size);

	for (int i = 0; i < MAX_CHARS_IN_FONT; i++)
	{
		if (!ft_isprint(i) && i != 0 && i != 10 && i != 32)
			continue ;
		printf("char: %c(%d), x:%d y:%d width:%d height:%d xoffset:%d yoffset:%d xadvance:%d\n",
			(char)i, i,
			font.characters[i].x, font.characters[i].y,
			font.characters[i].width, font.characters[i].height,
			font.characters[i].x_off, font.characters[i].y_off, font.characters[i].x_advance);
	}
}
