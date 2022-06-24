/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_walls_generation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:38:44 by njennes           #+#    #+#             */
/*   Updated: 2022/06/24 15:08:03 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "leaky.h"
#include "mlx.h"
#include "core.h"

void			create_texture_wall(t_texture *tex);
void			create_texture_vflip(t_texture *tex);
void			create_texture_grayscale(t_texture *tex);
void			create_texture_inversed(t_texture *tex);
void			create_texture_inverse_grayscale(t_texture *tex);

inline static t_rgb	**allocate_texture(t_texture *tex, int64_t width, int64_t height);

void	create_texture_variations(t_texture *tex)
{
	tex->wall = allocate_texture(tex, tex->width, tex->height);
	tex->wall_flip = allocate_texture(tex, tex->width, tex->height);
	tex->grayscale_handle = mlx_new_image(get_mlx(), tex->width, tex->height);
	tex->inversed_handle = mlx_new_image(get_mlx(), tex->width, tex->height);
	tex->inversed_grayscale_handle = mlx_new_image(get_mlx(),
		tex->width, tex->height);
}

void	shade_texture_variations(t_texture *tex)
{
	create_texture_wall(tex);
	create_texture_vflip(tex);
	create_texture_grayscale(tex);
	create_texture_inversed(tex);
	create_texture_inverse_grayscale(tex);
}

inline static t_rgb	**allocate_texture(t_texture *tex, int64_t width, int64_t height)
{
	int64_t	i;
	int64_t	j;
	t_rgb	**tab;

	tab = gc_calloc(width, sizeof (t_rgb *));
	i = 0;
	while (i < width)
	{
		tab[i] = gc_calloc(height, sizeof (t_rgb));
		j = 0;
		while (j < height)
		{
			tab[i][j] = tex->original[i + j * tex->width];
			j++;
		}
		i++;
	}
	return (tab);
}
