/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:36:50 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/11 19:12:20 by cybattis         ###   ########.fr       */
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

void	update_ui_flags(uint8_t flag)
{
	t_mlx	*app;

	app = get_app();
	if (app->ui.debug_ui & flag)
		app->ui.debug_ui ^= flag;
	else
		app->ui.debug_ui |= flag;
}
