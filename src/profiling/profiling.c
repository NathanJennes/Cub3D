/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profiling.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:34:37 by njennes           #+#    #+#             */
/*   Updated: 2022/05/26 12:40:00 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
# include "profiling.h"

void __cyg_profile_func_enter(void *this_func, void *call_site)
NOPROF;
void __cyg_profile_func_exit(void *this_func, void *call_site)
NOPROF;

void __cyg_profile_func_enter(void *this_func, void *call_site)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	dprintf(2, "> %p %ld %d\n", this_func, time.tv_sec - 1653000000, time.tv_usec);
}

void __cyg_profile_func_exit(void *this_func, void *call_site)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	dprintf(2, "< %p %ld %d\n", this_func, time.tv_sec - 1653000000, time.tv_usec);
}