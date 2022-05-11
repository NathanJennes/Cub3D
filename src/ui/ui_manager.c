/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:00:13 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/11 19:01:38 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"

int	ui_main_menu(void)
{
	t_mlx	*app;

	app = get_app();
	put_xpm_to_window("assets/ui/select_bar.xpm", app->ui.select_bar_pos);
	put_xpm_to_window("assets/ui/main_menu.xpm", vec2(0, 0));
	return (0);
}

//int	ui_button(char *path, t_vec2 pos, t_vec2 clic_zone, int (*event)(void))
//{
//	put_png_to_window(path, (int)pos.x, (int)pos.y);
//	return (0);
//}

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
