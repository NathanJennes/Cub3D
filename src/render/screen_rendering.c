/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_rendering.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:58:56 by njennes           #+#    #+#             */
/*   Updated: 2022/05/26 18:34:30 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int	pixel_in_screen(int64_t x, int64_t y) NOPROF;

void	clear_screen(int color)
{
	int64_t	i;
	int64_t	total;
	int64_t	*pixels;
	int64_t	col;

	pixels = (int64_t *)get_frame()->addr;
	((int *)&col)[0] = color;
	((int *)&col)[1] = color;
	total = WIN_W * WIN_H / 2;
	i = 0;
	while (i < total)
	{
			pixels[i] = col;
			i++;
	}
}

void	set_screen_pixel(int64_t x, int64_t y, int color)
NOPROF
{
	char	*dst;
	t_frame	*frame;

	if (!pixel_in_screen(x, y))
		return ;
	frame = get_frame();
	dst = frame->addr
		+ (y * frame->line_length + x * 4);
	*(unsigned int *)dst = color;
}

void	set_screen_pixel_unsafe(int64_t x, int64_t y, int color)
NOPROF
{
	char	*dst;
	t_frame	*frame;

	frame = get_frame();
	dst = frame->addr
		+ (y * frame->line_length + x * 4);
	*(unsigned int *)dst = color;
}

static int	pixel_in_screen(int64_t x, int64_t y)
NOPROF
{
	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return (0);
	return (1);
}
