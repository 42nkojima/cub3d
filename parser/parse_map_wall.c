/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 09:17:39 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/23 09:31:06 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static bool	is_floor(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static bool	is_outside(t_vars *vars, int y, int x)
{
	if (y < 0 || y >= vars->height || x < 0 || x >= vars->width)
		return (true);
	return (vars->map[y][x] == ' ');
}

/*
** 歩けるマスの上下左右に、マップの外かスペースがあったら囲まれていない。
** 斜めは見なくていい。DDA も移動も x と y を片方ずつしか進まないので、
** 斜めの隙間からは抜けられない。
*/
bool	is_map_closed(t_vars *vars)
{
	int	y;
	int	x;

	y = 0;
	while (y < vars->height)
	{
		x = 0;
		while (x < vars->width)
		{
			if (is_floor(vars->map[y][x]) && (is_outside(vars, y - 1, x)
					|| is_outside(vars, y + 1, x) || is_outside(vars, y, x - 1)
					|| is_outside(vars, y, x + 1)))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}
