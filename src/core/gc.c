/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:51:26 by njennes           #+#    #+#             */
/*   Updated: 2022/07/12 17:07:58 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

inline static int	gc_callback(void *ptr);

void	init_gc(void)
{
	gc_set_callback(gc_callback);
}

inline static int	gc_callback(void *ptr)
{
	(void)ptr;
	error_close_app();
	return (1);
}
