/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:19:19 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/18 16:04:54 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# define RAY_LENGTH 1000
# define SIDE_X 1
# define SIDE_Y 2

# include "colors.h"

void		clear_screen(int color);
void		set_screen_pixel(int64_t x, int64_t y, int color);
int			color_lerp(int col1, int col2, float value);

void		draw_circle(t_ivec2 pos, float diameter, int color);
void		draw_rect(t_ivec2 pos, t_ivec2 size, int color);
void		draw_line(t_ivec2 start, t_ivec2 end, int col1, int col2);
void		render_text(const char *text, t_ivec2 pos);
int			outside_mmap_bounds(int x, int y);

void		render_ui_texture(int64_t tex_id, int64_t x, int64_t y);
void		render_ui_texture_grayscale(int64_t tex_id, int64_t x, int64_t y);
void		render_ui_texture_inversed(int64_t tex_id, int64_t x, int64_t y);
void		render_ui_texture_inverse_grayscale(int64_t tex_id, int64_t x, int64_t y);

void		render_ui_label(t_label *label);

void		render_walls(int fov);
float		shoot_ray(t_vec2 ray, t_vec2 pos, t_ivec2 map_pos);

#endif
