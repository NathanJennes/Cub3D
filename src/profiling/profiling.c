/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profiling.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:34:37 by njennes           #+#    #+#             */
/*   Updated: 2022/05/25 13:42:22 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>

void __cyg_profile_func_enter(void *this_func, void *call_site)
__attribute__((no_instrument_function));
void __cyg_profile_func_exit(void *this_func, void *call_site)
__attribute__((no_instrument_function));

void __cyg_profile_func_enter(void *this_func, void *call_site)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	printf("--> %p %p %ld %d\n", this_func, call_site, time.tv_sec, time.tv_usec);
}

void __cyg_profile_func_exit(void *this_func, void *call_site)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	printf("<-- %p %p %ld %d\n", this_func, call_site, time.tv_sec, time.tv_usec);
}