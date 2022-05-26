/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:44:26 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/26 16:31:05 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "profiling.h"

int trgb(int t, int r, int g, int b)
NOPROF
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int get_t(int trgb)
NOPROF
{
	return ((trgb >> 24) & 0xFF);
}

int get_r(int trgb)
NOPROF
{
	return ((trgb >> 16) & 0xFF);
}

int get_g(int trgb)
NOPROF
{
	return ((trgb >> 8) & 0xFF);
}

int get_b(int trgb)
NOPROF
{
	return (trgb & 0xFF);
}
