/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:38:00 by njennes           #+#    #+#             */
/*   Updated: 2022/06/23 13:56:11 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include <stdint.h>
# include "libft.h"
# include "profiling.h"

# define INVALID_TEXTURE -1

typedef union u_rgb	t_rgb;

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
	char	*name;
	int64_t	id;
	int		bpp;
	int		line_size;
	int		endian;
	int		width;
	int		height;
	void	*original_handle;
	t_rgb	*original;
	t_rgb	*grayscale;
	void	*grayscale_handle;
	t_rgb	*inversed_grayscale;
	void	*inversed_grayscale_handle;
	t_rgb	*inversed;
	void	*inversed_handle;
	t_rgb	**vflip;
	t_rgb	**ao_flat;
	t_rgb	**ao_right;
	t_rgb	**ao_left;
	t_rgb	**ao_all;
}	t_texture;

typedef struct s_texture_manager
{
	t_texture	*tex_array;
	int64_t		tex_array_size;
}	t_texture_manager;

/* Core */
void		init_texture_manager(void);
int			load_xpm(t_xpm_file *xpm_out, char *path);
t_texture	create_texture_from_xpm_file(t_xpm_file file);
t_texture	create_blank_texture(int width, int height);
void		free_texture(t_texture *texture);

int64_t		load_texture(char *path);
int64_t		new_texture(int width, int height);
void		finish_new_texture(int64_t tex_id);
void		update_texture_variations(int64_t tex_id);
void		unload_texture_manager(void);
t_texture	*get_texture_from_id(int64_t tex_id);

/* Utils */
t_ivec2		get_texture_size(int64_t tex_id) NOPROF;

#endif
