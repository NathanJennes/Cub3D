/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:51:10 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/29 15:50:39 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "core.h"
#include "leaky.h"
#include "render.h"

int	close_app()
{
	shutdown_renderer();
	if (get_app()->state == IN_GAME && get_app()->gamestate.name)
		save_game(get_app()->gamestate.name);
	save_settings(get_settings());
	destroy_window();
	unload_texture_manager();
	unload_saves();
	clear_sprite_manager();
	gc_clean();
	exit(EXIT_SUCCESS);
}

void	error_close_app(void)
{
	shutdown_renderer();
	destroy_window();
	unload_texture_manager();
	unload_saves();
	clear_sprite_manager();
	gc_clean();
	printf("Error\n");
	exit(EXIT_FAILURE);
}
