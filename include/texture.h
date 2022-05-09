/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:38:00 by njennes           #+#    #+#             */
/*   Updated: 2022/05/09 22:36:53 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

typedef struct s_xpm_file
{
	void	*handle;
	uint8_t	*data;
	int		bpp;
	int		line_size;
	int		endian;
	int		width;
	int		height;
}	t_xpm_file;

typedef struct s_texture
{
	int		id;
	int		bpp;
	int		line_size;
	int		endian;
	int		width;
	int		height;
	void	*original_handle;
	uint8_t	*original;
	uint8_t	*ao_flat;
	uint8_t	*ao_right;
	uint8_t	*ao_left;
	uint8_t	*ao_all;
}	t_texture;

t_xpm_file	load_xpm(char *path);
t_texture	create_texture_from_xpm_file(t_xpm_file file);

#endif
