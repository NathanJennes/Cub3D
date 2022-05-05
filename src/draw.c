/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:56:16 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/05 13:39:32 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int	draw_frame(t_mlx *app)
{
	clear_screen(app, BKGD_COLOR);
	render_map(app, 2);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
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
