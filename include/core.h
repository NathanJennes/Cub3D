/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:33:14 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/05 14:02:29 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "mlx.h"
# include "libft.h"

# ifdef FULL_SCREEN
#  define WIN_W		1920
#  define WIN_H		1080
# else
#  define WIN_W		960
#  define WIN_H		540
# endif

# define MMAP_W				500
# define MMAP_H				500
# define MMAP_PAD			20
# define MMAP_ZOOM_FACTOR	20
# define MMAP_PLAYER_DIAM	10

# define CELL_WIDTH		50
# define CELL_HEIGHT	50

# define WALL		1
# define EMPTY		0
# define VOID		-1

# define BKGD_COLOR	0x0037464B

typedef struct s_map_info
{
	size_t	width;
	size_t	height;
	t_vec2	spawn_pos;
	char	spawn_dir;
	t_vec3	ceiling_color;
	t_vec3	floor_color;
	char	*no_tex;
	char	*ea_tex;
	char	*so_tex;
	char	*we_tex;
	int		**map;
	char	**map_raw;
}	t_map_info;

typedef struct s_frame
{
	void	*img;
	char	*addr;
	int		bits_pp;
	int		line_length;
	int		endian;
}	t_frame;

typedef struct s_player
{
	t_vec2	pos;
	float	direction;
}	t_player;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_frame		frame;
	t_map_info	map;
	t_player	player;
}	t_mlx;

/* core.c */
void		init_window(t_mlx *app, char *win_name);
int			close_app(t_mlx *app);
void		error_close_app(t_mlx *app);
int			error_code_msg(int code, char *msg);
void		check_leaky_errors(void);

/* initialization */
int			is_legal_file(int argc, char **argv);
t_mlx		*init_app(char *file);
void		init_gc(void);
void		post_init_gc(t_mlx *app);

/* draw.c */
void		clear_screen(t_mlx *app, int color);
int			draw_frame(t_mlx *app);
void		mlx_pixel_put_img(t_frame *frame, int x, int y, int color);

/* rendering */
void		render_mmap(t_mlx *app, int zoom);
void		render_circle(t_frame *frame, t_vec2 pos, int diameter, int color);

/* hooks.c.c */
int			key_hooks(int keycode, t_mlx *app);
int			mouse_hooks(int mousecode, int x, int y);

#endif
