/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:27:01 by cybattis          #+#    #+#             */
/*   Updated: 2022/04/22 14:52:04 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void	ft_ferror(int fd)
{
	if (fd < 0)
	{
		dprintf(2, "Error: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void	ft_error_msg(char *msg)
{
	dprintf(2, "Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

void	ft_free_2d(void **ptr, int i)
{
	while (i)
		free(ptr[i--]);
	free(ptr[i]);
	free(ptr);
}
