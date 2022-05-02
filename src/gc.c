/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:51:26 by njennes           #+#    #+#             */
/*   Updated: 2022/05/02 14:03:25 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"

static int	gc_callback(void *ptr);

void	init_gc(void)
{
	gc_ignore_warnings(0);
	gc_clean_on_error(0);
	gc_set_callback(gc_callback);
	gc_set_callback_param(NULL);
	gc_set_default_capacity(10);
}

static int	gc_callback(void *ptr)
{
	size_t	i;

	(void)ptr;
	if (gc_strarray_size((char **) gc_get_errors()) == 0)
		return (error_code_msg(0, "Leaky has no errors\n"));
	printf("Leaky has errors\n");
	i = 0;
	while (i < gc_strarray_size((char **) gc_get_errors()))
	{
		printf("Error[%lu]: %s\n", i, gc_get_errors()[i]);
		i++;
	}
	return (1);
}
