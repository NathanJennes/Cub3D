/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:11:29 by njennes           #+#    #+#             */
/*   Updated: 2022/05/05 13:38:19 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "error_utils.h"

static void	draw_cells(t_mlx *app, int cell_size);
static void	render_mmap_wall(t_mlx *app, int x, int y, int cell_size);
static void	render_mmap_empty(t_mlx *app, int x, int y, int cell_size);

void	render_map(t_mlx *app, int zoom)
{
	int			cell_size;

	cell_size = MMAP_ZOOM_FACTOR * zoom;
	draw_cells(app, cell_size);
}

static void	draw_cells(t_mlx *app, int cell_size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < app->map.height)
	{
		j = 0;
		while (j < app->map.width)
		{
			if (app->map.map[i][j] == WALL)
				render_mmap_wall(app, MMAP_PAD + j * cell_size,
						MMAP_PAD + i * cell_size, cell_size);
			if (app->map.map[i][j] == EMPTY)
				render_mmap_empty(app, MMAP_PAD + j * cell_size,
						MMAP_PAD + i * cell_size, cell_size);
			j++;
		}
		i++;
	}
}

static void	render_mmap_wall(t_mlx *app, int x, int y, int cell_size)
{
	int	i;
	int	j;

	i = 0;
	while (i < cell_size)
	{
		j = 0;
		while (j < cell_size)
		{
			mlx_pixel_put_img(&app->frame, x + j, y + i,
					create_trgb(0, 150, 150, 150));
			j++;
		}
		i++;
	}
}

static void	render_mmap_empty(t_mlx *app, int x, int y, int cell_size)
{
	int	i;
	int	j;

	i = 0;
	while (i < cell_size)
	{
		j = 0;
		while (j < cell_size)
		{
			mlx_pixel_put_img(&app->frame, x + j, y + i,
					create_trgb(0, 250, 250, 250));
			j++;
		}
		i++;
	}
}
