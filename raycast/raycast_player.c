/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 16:24:38 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/11 19:05:12 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <math.h>

/*
** Sets the player position and direction from N, S, W or E in the map.
** pos   : +0.5 to stand in the middle of the cell.
** dir   : picked from the table in t_dir order (NORTH, SOUTH, WEST, EAST).
**         y grows downward, so north is (0, -1).
** plane : dir turned 90 degrees right (-dir_y, dir_x), times PLANE_LEN.
**         If it does not match dir, the screen is mirrored or distorted.
*/
void	raycast_init_player(t_vars *v)
{
	static const double	dirs[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

	v->player.pos_x = v->col + 0.5;
	v->player.pos_y = v->row + 0.5;
	v->player.dir_x = dirs[v->direction][0];
	v->player.dir_y = dirs[v->direction][1];
	v->player.plane_x = -v->player.dir_y * PLANE_LEN;
	v->player.plane_y = v->player.dir_x * PLANE_LEN;
}

/*
** Rotates the vector (x, y) by angle (in radians).
** Uses the rotation formula: https://mathlandscape.com/rotation-matrix/
** The old x is kept, as y would otherwise be computed with the new x.
** y grows downward, so a positive angle turns clockwise on screen.
*/
static void	raycast_rotate_vec(double *x, double *y, double angle)
{
	double	old_x;

	old_x = *x;
	*x = old_x * cos(angle) - *y * sin(angle);
	*y = old_x * sin(angle) + *y * cos(angle);
}

/*
** Rotates the player direction by angle.
** dir and plane turn by the same angle, so their lengths and the right
** angle between them stay the same and the screen is not distorted.
*/
void	raycast_rotate(t_player *p, double angle)
{
	raycast_rotate_vec(&p->dir_x, &p->dir_y, angle);
	raycast_rotate_vec(&p->plane_x, &p->plane_y, angle);
}

/*
** Moves the player by MOVE_SPEED toward (dx, dy), but not into a wall cell.
** In a wall cell the DDA would start inside a wall and break the drawing,
** and leaving the map would crash.
** x and y are checked separately, so the player slides along a wall
** when hitting it at an angle.
** The parser makes sure the map is closed, so checking for '1' is enough.
*/
void	raycast_move(t_player *p, char **map, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = p->pos_x + dx * MOVE_SPEED;
	new_y = p->pos_y + dy * MOVE_SPEED;
	if (map[(int)p->pos_y][(int)new_x] != '1')
		p->pos_x = new_x;
	if (map[(int)new_y][(int)p->pos_x] != '1')
		p->pos_y = new_y;
}
