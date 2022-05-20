/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:19:19 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/18 16:51:48 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# define RAY_LENGTH 1000
# define SIDE_X 1
# define SIDE_Y 2

# include <stddef.h>

/* Screen drawing */
void		clear_screen(int color);
void		set_screen_pixel(int64_t x, int64_t y, int color);

void		draw_circle(t_ivec2 pos, int64_t diameter, int color);
void		draw_rect(t_ivec2 pos, t_ivec2 size, int color);
void		draw_line(t_ivec2 start, t_ivec2 end, int col);
void		draw_line_lerp(t_ivec2 start, t_ivec2 end, int col1, int col2);
void		render_text(char *text, t_ivec2 pos);

/* Texture drawing */
void		draw_rect_tex(t_ivec2 pos, t_ivec2 size, int color, int64_t tex_id);
void		draw_circle_tex(t_ivec2 pos, int64_t diameter, int color, int64_t tex_id);
void		draw_line_tex(t_ivec2 start, t_ivec2 end, int col, int64_t tex_id);
void		draw_line_lerp_tex(t_ivec2 start, t_ivec2 end, int col1, int col2, int64_t tex_id);

void		clear_texture(int color, int64_t tex_id);
void		set_texture_pixel(int64_t x, int64_t y, int color, int64_t tex_id);

/* Texture rendering */
void		render_ui_texture(int64_t tex_id, int64_t x, int64_t y);
void		render_ui_texture_grayscale(int64_t tex_id, int64_t x, int64_t y);
void		render_ui_texture_inversed(int64_t tex_id, int64_t x, int64_t y);
void		render_ui_texture_inverse_grayscale(int64_t tex_id, int64_t x, int64_t y);

/* Walls rendering */
void		render_walls(int fov);
float		shoot_ray(t_vec2 ray, t_vec2 pos, t_ivec2 map_pos);

/* Utils */
int			outside_mmap_bounds(int x, int y);

#endif
