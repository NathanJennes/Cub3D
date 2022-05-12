/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:19:19 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/09 16:29:43 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

#include "colors.h"

void		clear_screen(int color);
void		mlx_pixel_put_img(int x, int y, int color);
int			color_lerp(int col1, int col2, float value);

void		render_circle(t_vec2 pos, float diameter, int color);
void		render_rect(t_vec2 pos, t_vec2 size, int color);
void		render_line(t_vec2 start, t_vec2 end, int col1, int col2);
int			outside_mmap_bounds(int x, int y);

#endif
