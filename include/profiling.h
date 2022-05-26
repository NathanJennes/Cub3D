/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profiling.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:39:06 by njennes           #+#    #+#             */
/*   Updated: 2022/05/26 12:39:19 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROFILING_H
# define PROFILING_H

# ifdef DEBUG_PROFILE
#  define NOPROF __attribute__((no_instrument_function))
# else
#  define NOPROF
# endif

#endif
