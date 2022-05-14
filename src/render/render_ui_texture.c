/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 12:37:18 by njennes           #+#    #+#             */
/*   Updated: 2022/05/14 12:41:21 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "core.h"

void	render_ui_texture(int64_t tex_id, int x, int y)
{
	t_mlx				*app;
	t_texture			*texture;

	texture = get_texture_from_id(tex_id);
	if (!texture)
		return ;
	app = get_app();
	mlx_put_image_to_window(app->mlx, app->win,
		texture->original_handle, x, y);
}
