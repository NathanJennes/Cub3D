/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:56:16 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/05 14:06:27 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int	draw_frame(t_mlx *app)
{
	clear_screen(app, BKGD_COLOR);
	render_mmap(app, 1);
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

static int	pixel_in_canvas(int x, int y)
{
	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return (0);
	return (1);
}

void	mlx_pixel_put_img(t_frame *frame, int x, int y, int color)
{
	char	*dst;

	if (!pixel_in_canvas(x, y))
		return ;
	dst = frame->addr
		+ (y * frame->line_length + x * (frame->bits_pp / 8));
	*(unsigned int *)dst = color;
}

void	render_circle(t_frame *frame, t_vec2 pos, int diameter, int color)
{
	int	i;
	int	j;
	int	diameter_2;

	i = -diameter / 2;
	diameter_2 = (diameter / 2) * (diameter / 2);
	while (i < diameter / 2)
	{
		j = -diameter / 2;
		while (j < diameter / 2)
		{
			if (i * i + j * j <= diameter_2)
				mlx_pixel_put_img(frame, pos.x + j, pos.y + i, color);
			j++;
		}
		i++;
	}
}
