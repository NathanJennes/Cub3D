/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_rendering.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:58:56 by njennes           #+#    #+#             */
/*   Updated: 2022/05/26 16:28:03 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int	pixel_in_screen(int64_t x, int64_t y) NOPROF;

void	clear_screen(int color)
{
	int		i;
	int		total;
	t_frame	*frame;

	frame = get_frame();
	i = 0;
	total = (WIN_W * WIN_H);
	while (i < total)
	{
		*((unsigned int *)(frame->addr + i * 4)) = color;
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
