/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stb47 <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:21:25 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/02 15:24:03 by stb47            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"

void	init_ui(void)
{
	t_ui	*ui;

	ui = get_ui();
	ui->state = MAIN_MENU;
	init_main_menu();
	init_new_game_menu();
	init_settings_menu();
}
