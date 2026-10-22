/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 17:35:10 by tmase             #+#    #+#             */
/*   Updated: 2026/10/23 06:37:32 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "libft.h"

# define WIN_W 640
# define WIN_H 480

typedef enum e_dir
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}				t_dir;

typedef struct s_img
{
	void		*ptr;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			w;
	int			h;
}				t_img;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_vars
{
	char		*tex_path[4];
	t_dir		direction;
	int			ceiling_color;
	int			floor_color;
	char		**map;
	int			width;
	int			height;
	int			col;
	int			row;
	void		*mlx;
	void		*win;
	t_img		img;
	t_img		tex[4];
	t_player	player;
}				t_vars;

#endif
