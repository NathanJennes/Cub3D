/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_helper_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:33:17 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/27 17:33:17 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"
#include "libft.h"

void	print_vec2(t_vec2 v, char *font, int size, t_ivec2 pos)
{
	char	buffer[64];

	snprintf(buffer, sizeof(buffer), "[%.4f, %.4f]", v.x, v.y);
	render_text(buffer, font, size, pos);
}

void	print_ivec2(t_ivec2 v, char *font, int size, t_ivec2 pos)
{
	char	buffer[16];

	snprintf(buffer, sizeof(buffer), "[%lld, %lld]", v.x, v.y);
	render_text(buffer, font, size, pos);
}
