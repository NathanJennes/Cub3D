/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:19:19 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/20 15:49:03 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# define RAY_LENGTH 10
# define SIDE_X 1
# define SIDE_Y 2

# include "colors.h"
# include "core.h"

void		clear_screen(int color);
void		mlx_pixel_put_img(int x, int y, int color);
int			color_lerp(int col1, int col2, float value);

void		render_circle(t_ivec2 pos, float diameter, int color);
void		render_rect(t_ivec2 pos, t_ivec2 size, int color);
void		render_line(t_ivec2 start, t_ivec2 end, int col1, int col2);
int			outside_mmap_bounds(int x, int y);

void		render_ui_texture(int64_t tex_id, int x, int y);
void		render_ui_texture_grayscale(int64_t tex_id, int x, int y);
void		render_ui_texture_inversed(int64_t tex_id, int x, int y);
void		render_ui_texture_inverse_grayscale(int64_t tex_id, int x, int y);

void		render_ui_label(t_label *label);
void		render_ui_img_box(t_img_box *img_box);
void		render_ui_button(t_button *button);

void		render_walls(void);
t_ray		shoot_ray(t_vec2 ray, t_ivec2 map_pos);

#endif
