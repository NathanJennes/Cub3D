/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_walls_generation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:38:44 by njennes           #+#    #+#             */
/*   Updated: 2022/06/15 15:06:44 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "leaky.h"
#include "mlx.h"
#include "core.h"

void			shade_ao_texture_flat(
					t_rgb **data, int width, int height);
void			shade_ao_texture_right(
					t_rgb **data, int width, int height);
void			shade_ao_texture_left(
					t_rgb **data, int width, int height);
void			shade_ao_texture_all(
					t_rgb **data, int width, int height);
void			create_texture_vflip(t_rgb **original, t_rgb **vflip, int width, int height);
void			create_texture_grayscale(t_texture *tex);
void			create_texture_inversed(t_texture *tex);
void			create_texture_inverse_grayscale(t_texture *tex);

inline static t_rgb	**allocate_texture(t_texture *tex, int64_t width, int64_t height);
inline static void		create_ui_texture_variations(t_texture *tex);

void	create_texture_variations(t_texture *tex)
{
	tex->ao_flat = allocate_texture(tex, tex->width, tex->height);
	tex->ao_right = allocate_texture(tex, tex->width, tex->height);
	tex->ao_left = allocate_texture(tex, tex->width, tex->height);
	tex->ao_all = allocate_texture(tex, tex->width, tex->height);
	tex->vflip = allocate_texture(tex, tex->width, tex->height);
	shade_ao_texture_flat(tex->ao_flat, tex->width, tex->height);
	shade_ao_texture_right(tex->ao_right, tex->width, tex->height);
	shade_ao_texture_left(tex->ao_left, tex->width, tex->height);
	shade_ao_texture_all(tex->ao_all, tex->width, tex->height);
	create_texture_vflip(tex->ao_flat, tex->vflip, tex->width, tex->height);
	create_ui_texture_variations(tex);
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
			tab[i][j].color = *(int *)(tex->original + i * 4 + j * tex->line_size);
			j++;
		}
		i++;
	}
	return (tab);
}

inline static void	create_ui_texture_variations(t_texture *tex)
{
	tex->grayscale_handle = mlx_new_image(get_mlx(), tex->width, tex->height);
	tex->inversed_handle = mlx_new_image(get_mlx(), tex->width, tex->height);
	tex->inversed_grayscale_handle = mlx_new_image(get_mlx(),
		tex->width, tex->height);
	create_texture_grayscale(tex);
	create_texture_inversed(tex);
	create_texture_inverse_grayscale(tex);
}
