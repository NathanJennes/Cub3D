/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:19:19 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/26 15:44:35 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <stddef.h>
# include <stdint.h>
# include "libft.h"
# include "profiling.h"
# include "core.h"
# include "font.h"

# define DFLT_SIZE	300

# define RAY_LENGTH 50

# define NOSIDE 0
# define SIDE_X 1
# define SIDE_Y 2

/* Screen drawing */
void			clear_screen(int color);
void			set_screen_pixel(int64_t x, int64_t y, int color) NOPROF;

void			draw_circle(t_ivec2 pos, int64_t diameter, int color);
void			draw_rect(t_ivec2 pos, t_ivec2 size, int color);
void			draw_line(t_ivec2 start, t_ivec2 end, int col);
void			draw_line_lerp(t_ivec2 start, t_ivec2 end, int col1, int col2);
void			mlx_render_text(char *text, t_ivec2 pos);

/* Texture drawing */
void			draw_rect_tex(t_ivec2 pos, t_ivec2 size, int color, int64_t tex_id);
void			draw_circle_tex(t_ivec2 pos, int64_t diameter,
					int col, int64_t tex_id);
void			draw_line_tex(t_ivec2 start, t_ivec2 end, int col, int64_t tex_id);
void			draw_line_lerp_tex(t_ivec2 start, t_ivec2 end,
					int col1, int col2, int64_t tex_id);

void			clear_texture(int color, int64_t tex_id);
void			set_texture_pixel(int64_t x, int64_t y, int color, int64_t tex_id) NOPROF;

/* Texture rendering */
void			render_ui_texture(int64_t tex_id, int64_t x, int64_t y);
void			render_ui_texture_grayscale(int64_t tex_id, int64_t x, int64_t y);
void			render_ui_texture_inversed(int64_t tex_id, int64_t x, int64_t y);
void			render_ui_texture_inverse_grayscale(int64_t tex_id,
					int64_t x, int64_t y);

/* Font rendering */
t_font_bitmap	load_bitmap_font(char *path);
void			unload_bitmap_font(t_font_bitmap *font);
int				load_font_meta(t_font *font, char *path);
void			render_text(char *text, char *font_name, int size, t_ivec2 pos);
void			render_text_tex(char *text, char *font_name, t_ivec2 pos,
					t_ivec2 size_id);

void			init_font_manager(void);
void			unload_font_manager(void);
t_font			*get_font(char *name) NOPROF;

int64_t			get_text_width(char *text, char *font_name, int size) NOPROF;
int64_t			get_text_height(char *text, char *font_name, int size) NOPROF;
int64_t			get_text_box_height(char *text, char *font_name, int size) NOPROF;
t_ivec2			get_text_size(char *text, char *font_name, int size) NOPROF;
t_ivec2			get_text_box_size(char *text, char *font_name, int size) NOPROF;

t_ivec2			text_center_height(char *text, char *font_name,
					int size, t_ivec2 pos) NOPROF;
t_ivec2			text_center_width(char *text, char *font_name,
					int size, t_ivec2 pos) NOPROF;
t_ivec2			text_center(char *text, char *font_name,
					int size, t_ivec2 pos) NOPROF;

/* Walls rendering */
void			render_walls(void);
t_ray			shoot_ray(t_vec2 ray, t_ivec2 hit_pos);

/* Utils */
int				outside_mmap_bounds(int x, int y) NOPROF;

#endif
