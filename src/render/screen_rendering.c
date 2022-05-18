/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_rendering.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:58:56 by njennes           #+#    #+#             */
/*   Updated: 2022/05/18 16:01:53 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int	pixel_in_screen(int64_t x, int64_t y);

void	clear_screen(int color)
{
	int		i;
	int		total;
	int		bytes_pp;
	t_frame	*frame;

	frame = get_frame();
	i = 0;
	total = (WIN_W * WIN_H);
	bytes_pp = frame->bits_pp / 8;
	while (i < total)
	{
		*((unsigned int *)(frame->addr + i * bytes_pp)) = color;
		i++;
	}
}

void	set_screen_pixel(int64_t x, int64_t y, int color)
{
	char	*dst;
	t_frame	*frame;

	if (!pixel_in_screen(x, y))
		return ;
	frame = get_frame();
	dst = frame->addr
		  + (y * frame->line_length + x * (frame->bits_pp / 8));
	*(unsigned int *)dst = color;
}

static int	pixel_in_screen(int64_t x, int64_t y)
{
	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return (0);
	return (1);
}