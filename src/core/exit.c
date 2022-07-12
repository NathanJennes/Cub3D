/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:51:10 by cybattis          #+#    #+#             */
/*   Updated: 2022/07/12 16:55:12 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "core.h"

int	close_app(void)
{
	destroy_window();
	gc_clean();
	exit(EXIT_SUCCESS);
}

void	error_close_app(void)
{
	destroy_window();
	gc_clean();
	printf("Error\n");
	exit(EXIT_FAILURE);
}
