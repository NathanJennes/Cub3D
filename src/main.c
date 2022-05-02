/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 18:35:28 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/02 14:36:21 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "core.h"
#include "leaky.h"

int	main(int argc, char **argv)
{
	t_mlx	*app;

	if (!is_legal_file(argc, argv))
		return (error_code_msg(1, "Error"));
	app = init_app(argv[1]);
	gc_clean();
	return (0);
}
