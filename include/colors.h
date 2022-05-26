/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:23:53 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/26 12:51:57 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include "profiling.h"

# define BLACK		0x00000000
# define RED		0x00FF0000
# define GREEN		0x0000FF00
# define BLUE		0x000000FF
# define WHITE		0x00FFFFFF
# define PINK		0x00FF00FF
# define YELLOW		0x00FFFF00
# define TURQUOISE	0x0000FFFF

/* colors */
int			trgb(int t, int r, int g, int b)
NOPROF;
int			get_t(int trgb)
NOPROF;
int			get_r(int trgb)
NOPROF;
int			get_g(int trgb)
NOPROF;
int			get_b(int trgb)
NOPROF;

/* colors utils */
int			color_lerp(int col1, int col2, float value);

#endif
