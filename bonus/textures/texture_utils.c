/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 22:37:39 by njennes           #+#    #+#             */
/*   Updated: 2022/05/16 22:39:13 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "libft.h"

t_ivec2	get_texture_size(int64_t tex_id)
{
	t_texture	*texture;

	texture = get_texture_from_id(tex_id);
	if (!texture)
		return (ivec2(0, 0));
	return (ivec2(texture->width, texture->height));
}
