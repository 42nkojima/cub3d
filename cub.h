/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 17:35:10 by tmase             #+#    #+#             */
/*   Updated: 2026/10/01 18:46:24 by tmase            ###   ########.fr       */
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
}	t_dir;

typedef struct  s_vars{
    char    *tex_path[4];
    t_dir     direction;
    int        top_color;
    int        bottom_color;
    char     **map;
    int        width;
    int        height;
    int        col;
    int        row;
}                       t_vars;

#endif