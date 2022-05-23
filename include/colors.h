/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:23:53 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/23 21:57:16 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# define BLACK		0x00000000
# define RED		0x00FF0000
# define GREEN		0x0000FF00
# define BLUE		0x000000FF
# define WHITE		0x00FFFFFF
# define PINK		0x00FF00FF
# define YELLOW		0x00FFFF00
# define TURQUOISE	0x0000FFFF

# define CEILLING		0x000099CC
# define FLOOR			0x00666666
# define WALL_COLOR_1	0x00e65c00
# define WALL_COLOR_2	0x00b34700

/* colors_utils.c */
int			create_trgb(int t, int r, int g, int b);
int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);

#endif
