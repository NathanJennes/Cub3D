/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyril <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:36:50 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/26 12:57:10 by Cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"
#include "libft.h"

int64_t	str_px_size(char *str)
{
	return ((int)ft_strlen(str) * 7);
}

void	handle_debug_ui(void)
{
	t_mlx	*app;

	app = get_app();
	if (app->ui.debug_state == LVL3)
	{
		app->ui.debug_state = NO_DEBUG;
		return ;
	}
	app->ui.debug_state++;
}

void	print_double(double val, char *font, int size, t_ivec2 pos)
{
	char	buffer[9];

	snprintf(buffer, sizeof(buffer), "%.6lf", val);
	render_text(buffer, font, size, pos);
}

void print_int(int val, char *font, int size, t_ivec2 pos)
{
	char	buffer[16];

	snprintf(buffer, sizeof(buffer), "%d", val);
	render_text(buffer, font, size, pos);
}

void print_vec2(t_vec2 v, char *font, int size, t_ivec2 pos)
{
	char	buffer[64];

	snprintf(buffer, sizeof(buffer), "[%.4f, %.4f]", v.x, v.y);
	render_text(buffer, font, size, pos);
}

void print_ivec2(t_ivec2 v, char *font, int size, t_ivec2 pos)
{
	char	buffer[16];

	snprintf(buffer, sizeof(buffer), "[%lld, %lld]", v.x, v.y);
	render_text(buffer, font, size, pos);
}
