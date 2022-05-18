/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:34:21 by njennes           #+#    #+#             */
/*   Updated: 2022/05/18 15:44:51 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "core.h"

void	render_text(const char *text, t_ivec2 pos)
{
	mlx_string_put(get_mlx(), get_app()->win,
		(int)pos.x, (int)pos.y, trgb(0, 255, 255, 255), text);
}
