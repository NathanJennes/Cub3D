/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_save.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:58:27 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/27 14:59:03 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"

void	free_save(t_gamestate *save)
{
	gc_free2d((void **) save->map.map, save->map.height);
	gc_free(save->name);
	free_lights(save);
}
