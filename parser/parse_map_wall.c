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

static bool	is_outside(t_vars *v, int y, int x)
{
	if (y < 0 || y >= v->height || x < 0 || x >= v->width)
		return (true);
	return (v->map[y][x] == ' ');
}

/*
** The map is not closed if a walkable cell has the outside or a space
** above, below, left or right of it.
** Diagonals do not matter: the DDA and the movement both advance x and y
** one at a time, so nothing can slip through a diagonal gap.
*/
bool	is_map_closed(t_vars *v)
{
	int	y;
	int	x;

	y = 0;
	while (y < v->height)
	{
		x = 0;
		while (x < v->width)
		{
			if (is_floor(v->map[y][x]) && (is_outside(v, y - 1, x)
					|| is_outside(v, y + 1, x) || is_outside(v, y, x - 1)
					|| is_outside(v, y, x + 1)))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}
