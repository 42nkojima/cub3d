/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 17:35:10 by tmase             #+#    #+#             */
/*   Updated: 2026/10/04 02:17:37 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

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
}			t_vars;

#endif
