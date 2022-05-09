/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:36:50 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/09 17:04:51 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "libft.h"

void	put_text(t_mlx *app, t_vec2 pos, int color, char *str)
{
	mlx_string_put(app->mlx, app->win, (int)pos.x, (int)pos.y, color, str);
}

int	str_px_size(char *str)
{
	return ((int)ft_strlen(str) * 6);
}
