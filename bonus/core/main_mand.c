/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:32:43 by njennes           #+#    #+#             */
/*   Updated: 2022/06/29 16:33:25 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"

int	main(int argc, char *argv[])
{
	if (argc == 2)
		init_app(argv[1]);
	else
	{
		printf("Wrong arg count\n");
		return (0);
	}
	mlx_loop(get_mlx());
	gc_clean();
	return (0);
}
