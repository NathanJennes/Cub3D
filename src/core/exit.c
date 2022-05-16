/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:51:10 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/16 18:48:42 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "core.h"
#include "leaky.h"

int	close_app(void)
{
	if (!save_game("save.save"))
		printf("Could not save game!\n");
	destroy_window();
	unload_texture_manager();
	unload_saves();
	gc_clean();
	exit(EXIT_SUCCESS);
}

void	error_close_app(void)
{
	check_leaky_errors();
	destroy_window();
	unload_texture_manager();
	unload_saves();
	gc_clean();
	printf("Error\n");
	exit(EXIT_FAILURE);
}

void	check_leaky_errors(void)
{
	size_t	i;

	if (gc_strarray_size((char **) gc_get_errors()) == 0)
		printf("Leaky has no errors\n");
	else
		printf("Leaky has errors\n");
	i = 0;
	while (i < gc_strarray_size((char **) gc_get_errors()))
	{
		printf("Error[%lu]: %s\n", i, gc_get_errors()[i]);
		i++;
	}
}
