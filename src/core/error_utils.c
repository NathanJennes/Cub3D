/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:27:01 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/02 13:43:38 by njennes          ###   ########.fr       */
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

int	error_code_msg(int code, char *msg)
{
	printf("%s\n", msg);
	return (code);
}

void	ft_free_2d(void **ptr, int i)
{
	while (i)
		free(ptr[i--]);
	free(ptr[i]);
	free(ptr);
}
