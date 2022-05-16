/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:21:25 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/16 17:30:22 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"

static void	init_slider(t_ui *ui);

void	init_ui(void)
{
	t_ui	*ui;

	ui = get_ui();
	ui->state = MAIN_MENU;
	load_texture("assets/ui/main_menu.xpm");
	load_texture("assets/ui/option_menu.xpm");
	load_texture("assets/ui/select_bar.xpm");
	ui->select_bar_pos = vec2(360, 170);
	init_slider(ui);
}

static void	init_slider(t_ui *ui)
{
	ui->map_scale_slider.pos = vec2(WIN_W - 150, 10);
	ui->map_scale_slider.increment_size = 0.1f;
	ui->map_scale_slider.value = 1.0f;
	ui->map_scale_slider.min = 0.2f;
	ui->map_scale_slider.max = 5.0f;
	ui->map_scale_slider.displayed = 1;
}
