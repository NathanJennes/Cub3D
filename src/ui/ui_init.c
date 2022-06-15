/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:21:25 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/15 17:25:32 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"

static void	init_mmap(void);

void	init_ui(void)
{
	t_ui	*ui;

	ui = get_ui();
	ui->state = MAIN_MENU;
	init_main_menu();
	init_new_game_menu();
	init_settings_menu();
	init_mmap();
}

static void	init_mmap(void)
{
	t_settings	*settings;
	t_mmap		*minimap;

	settings = get_settings();
	minimap = &get_ui()->minimap;
	minimap->mmap_h = settings->win_h / 6;
	minimap->mmap_w = settings->win_w / 8;
	minimap->mmap_halfh = minimap->mmap_h / 2;
	minimap->mmap_halfw = minimap->mmap_w / 2;
}
