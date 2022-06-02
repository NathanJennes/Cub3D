/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 18:35:28 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/20 17:22:10 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"

int	main(int argc, char *argv[])
{
	if (argc == 2)
		init_app_linux(argv[1]);
	else
		init_app();
	mlx_loop(get_mlx());
	gc_clean();
	return (0);
}
