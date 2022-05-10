/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:00:13 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/10 21:47:34 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"

int	ui_main_menu(void)
{
	int 	img_width;
	int 	img_height;
	void	*menu;
	t_mlx	*app;

	app = get_app();
	menu = mlx_xpm_file_to_image(app->mlx, "assets/ui/main_menu.xpm",
			&img_width, &img_height);
	if (!menu)
	{
		dprintf(STDERR_FILENO, "Error img path\n");
		error_close_app();
	}
	mlx_put_image_to_window(app->mlx, app->win, menu, 0, 0);
	mlx_destroy_image(app->mlx, menu);
	return (0);
}

int	ui_button(char *path, t_vec2 pos, t_vec2 clic_zone, int (*event)(void))
{
	int 	img_width;
	int 	img_height;
	void	*img;

	img = mlx_xpm_file_to_image(app->mlx, path,
			&img_width, &img_height);
	if (!menu)
	{
		dprintf(STDERR_FILENO, "Error img path\n");
		error_close_app();
	}
	put_img_to_window(path, posx, posy);
	if (event)
		event();
	return (0);
}

int put_img_to_window(char *path, int posx, int posy)
{
	int 	img_width;
	int 	img_height;
	void	*img;
	t_mlx	*app;

	app = get_app();
	img = mlx_xpm_file_to_image(app->mlx, path, &img_width, &img_height);
	mlx_put_image_to_window(app->mlx, app->win, img, posx, posy);
	mlx_destroy_image(app->mlx, img);
	return (0);
}
