/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:42:21 by njennes           #+#    #+#             */
/*   Updated: 2022/05/25 17:42:49 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_H
# define FONT_H

# include "libft.h"

# define MAX_CHARS_IN_FONT 256
# define FONT_SAMPLING 2

typedef struct s_font_bitmap
{
	int		width;
	int		height;
	int		bpp;
	int		endian;
	int		line_size;
	uint8_t	*data;
}	t_font_bitmap;

typedef struct s_char_meta
{
	int		x;
	int		y;
	int		width;
	int		height;
	int		x_off;
	int		y_off;
	int		x_advance;
}	t_char_meta;

typedef struct s_font_meta
{
	t_font_bitmap	bitmap;
	t_char_meta		characters[MAX_CHARS_IN_FONT];
	char			*name;
	int				font_size;
}	t_font;

typedef struct s_text_render
{
	t_font			*font;
	t_char_meta		*c;
	t_font_bitmap	*bitmap;
	double			ratio;
	t_ivec2			xy;
	t_ivec2			pos;
	t_ivec2			px_size;
}	t_text_render;

typedef struct s_font_manager
{
	t_font		*fonts;
	int64_t		font_count;
}	t_font_manager;

#endif
