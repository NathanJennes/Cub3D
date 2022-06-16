/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:36:50 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/15 15:46:43 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"
#include "libft.h"

int64_t	str_px_size(char *str)
{
	return ((int)ft_strlen(str) * 7);
}

void	switch_debug_ui(void)
{
	t_mlx	*app;

	app = get_app();
	if (app->ui.debug == TRUE)
		app->ui.debug = FALSE;
	else
		app->ui.debug = TRUE;
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
