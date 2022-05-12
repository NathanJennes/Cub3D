/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 22:20:46 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/12 22:20:46 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int	put_xpm_to_window(char *path, t_vec2 pos)
{
	int		img_width;
	int		img_height;
	void	*img;
	t_mlx	*app;

	app = get_app();
	img = mlx_xpm_file_to_image(app->mlx, path, &img_width, &img_height);
	if (!img)
	{
		dprintf(STDERR_FILENO, "Error img path\n");
		error_close_app();
	}
	mlx_put_image_to_window(app->mlx, app->win, img, (int)pos.x, (int)pos.y);
	mlx_destroy_image(app->mlx, img);
	return (0);
}
