/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:03:11 by njennes           #+#    #+#             */
/*   Updated: 2022/05/18 16:03:30 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "libft.h"

int	color_lerp(int col1, int col2, double value)
{
	t_vec3	new_color;

	new_color.x = get_r(col1) + value * (get_r(col2) - get_r(col1));
	new_color.y = get_g(col1) + value * (get_g(col2) - get_g(col1));
	new_color.z = get_b(col1) + value * (get_b(col2) - get_b(col1));
	return (trgb(0, new_color.x, new_color.y, new_color.z));
}
