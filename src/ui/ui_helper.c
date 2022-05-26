/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:36:50 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/26 13:53:46 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "libft.h"

void	put_text(t_ivec2 pos, int color, char *str)
{
	t_mlx	*app;

	app = get_app();
	mlx_string_put(app->mlx, app->win, (int)pos.x, (int)pos.y, color, str);
}

int	str_px_size(char *str)
{
	return ((int)ft_strlen(str) * 7);
}

void	switch_debug_ui(void)
{
	t_mlx	*app;

	app = get_app();
	if (app->ui.debug_ui == TRUE)
		app->ui.debug_ui = FALSE;
	else
		app->ui.debug_ui = TRUE;
}

void	print_float(double val, t_ivec2 pos, int color)
{
	char	buffer[9];

	snprintf(buffer, sizeof(buffer), "%.6lf", val);
	put_text(pos, color, buffer);
}

void	print_ivec(t_ivec2 v, t_ivec2 pos, int color)
{
	char	buffer[16];

	snprintf(buffer, sizeof(buffer), "[%lld, %lld]", v.x, v.y);
	put_text(pos, color, buffer);
}

void	print_int(int val, t_ivec2 pos, int color)
{
	char	buffer[16];

	snprintf(buffer, sizeof(buffer), "%d", val);
	put_text(pos, color, buffer);
}

void	print_vec(t_vec2 v, t_ivec2 pos, int color)
{
	char	buffer[64];

	snprintf(buffer, sizeof(buffer), "[%.4f, %.4f]", v.x, v.y);
	put_text(pos, color, buffer);
}
