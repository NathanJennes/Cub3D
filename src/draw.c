/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:56:16 by cybattis          #+#    #+#             */
/*   Updated: 2022/04/20 21:08:04 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int	draw_frame(t_mlx *fdf)
{
	clear_screen(fdf, BKGD_COLOR);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->frame.img, 0, 0);
	return (0);
}

void	clear_screen(t_mlx *app, int color)
{
	int	i;
	int	total;
	int	bytes_pp;

	i = 0;
	total = (WIN_W * WIN_H) - 1;
	bytes_pp = app->frame.bits_pp / 8;
	while (i < total)
	{
		*((unsigned int *)(app->frame.addr + i * bytes_pp)) = color;
		i++;
	}
}

void	mlx_pixel_put_img(t_frame *frame, int x, int y, int color)
{
	char	*dst;

	dst = frame->addr
		+ (y * frame->line_length + x * (frame->bits_pp / 8));
	*(unsigned int *)dst = color;
}
