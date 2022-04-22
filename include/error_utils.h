/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:53:13 by cybattis          #+#    #+#             */
/*   Updated: 2022/04/22 14:53:13 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_UTILS_H
# define ERROR_UTILS_H

# define BLACK		0x00000000
# define RED		0x00FF0000
# define GREEN		0x0000FF00
# define BLUE		0x000000FF
# define WHITE		0x00FFFFFF
# define PINK		0x00FF00FF
# define YELLOW		0x00FFFF00
# define TURQUOISE	0x0000FFFF

/* error_utils.c */
void		ft_ferror(int fd);
void		ft_error_msg(char *msg);
void		ft_free_2d(void **ptr, int i);

/* colors_utils.c */
int			create_trgb(int t, int r, int g, int b);
int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);

#endif
