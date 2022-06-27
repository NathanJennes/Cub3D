/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:53:13 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/27 18:02:19 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_UTILS_H
# define ERROR_UTILS_H

# include "profiling.h"

# define RETURN_SUCCESS 1
# define ERR_EMPTY_FILE -1
# define ERR_FONT_META_INFO_NOT_FOUND -2
# define ERR_FONT_META_NAME_NOT_FOUNT -3
# define ERR_FONT_META_SIZE_NOT_FOUND -4
# define ERR_FONT_META_SIZE_ZERO -5
# define ERR_FONT_META_CHAR_ID_NOT_FOUND -6
# define ERR_FONT_META_FIELD_NAME_NO_MATCH -7
# define ERR_FONT_META_NO_EQUAL_AFTER_FIELD -8
# define ERR_FONT_META_REACHED_EOF -9

/* error_utils.c */
void		ft_ferror(int fd);
void		ft_error_msg(char *msg);
void		ft_free_2d(void **ptr, int i);
int			error_code_msg(int code, char *msg);

int			print_cub_err(int err);

#endif
