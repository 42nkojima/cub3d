/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 17:35:10 by tmase             #+#    #+#             */
/*   Updated: 2026/10/08 22:00:54 by tmase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

#include "libft.h"

typedef enum e_dir
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}			t_dir;

typedef struct s_vars
{
	char	*tex_path[4];
	t_dir	direction;
	int		ceiling_color;
	int		floor_color;
	char	**map;
	int		width;
	int		height;
	int		col;
	int		row;
	void	*mlx;
	void	*win;
}			t_vars;

#endif

	