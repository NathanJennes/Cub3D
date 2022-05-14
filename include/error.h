/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 15:40:31 by njennes           #+#    #+#             */
/*   Updated: 2022/05/14 15:49:05 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum e_error : int
{
	NONE = 0,
	RESSOURCE_NOT_FOUND = 1,
}	t_error;


void	cub_set_error(t_error error);
void	cub_unset_error(void);
int		cub_has_error(void);
int		cub_get_error(void);
int		cub_consume_error(void);

#endif
