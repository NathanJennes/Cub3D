/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:56:16 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/05 15:44:11 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int	pixel_in_canvas(int x, int y);

void	clear_screen(int color)
{
	int	i;
	int	total;
	int	bytes_pp;
	t_frame	*frame;

	frame = get_frame();
	i = 0;
	total = (WIN_W * WIN_H) - 1;
	bytes_pp = frame->bits_pp / 8;
	while (i < total)
	{
		*((unsigned int *)(frame->addr + i * bytes_pp)) = color;
		i++;
	}
}

void	mlx_pixel_put_img(int x, int y, int color)
{
	char	*dst;
	t_frame	*frame;

	if (!pixel_in_canvas(x, y))
		return ;
	frame = get_frame();
	dst = frame->addr
		+ (y * frame->line_length + x * (frame->bits_pp / 8));
	*(unsigned int *)dst = color;
}

static int	pixel_in_canvas(int x, int y)
{
	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return (0);
	return (1);
}
