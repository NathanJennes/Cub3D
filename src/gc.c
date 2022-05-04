/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:51:26 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 17:33:16 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"

static int	gc_callback(void *ptr);

void	init_gc(void)
{
	gc_clean_on_error(0);
	gc_set_callback(gc_callback);
	gc_set_default_capacity(1);
}

void	post_init_gc(t_mlx *app)
{
	gc_set_callback_param(app);
}

static int	gc_callback(void *ptr)
{
	error_close_app(ptr);
	return (1);
}
