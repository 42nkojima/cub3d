/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 16:18:18 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/11 17:36:03 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <math.h>

/*
** Sets the direction and the start cell of the ray for column x.
** camera_x   : column x mapped to -1 (left edge) .. +1 (right edge).
**              x is 0 .. WIN_W - 1, so 2 * x / WIN_W gives 0 .. 2, minus 1.
** r->dir     : ray direction: p->dir (from the eye to the screen center)
**              plus p->plane (from the center to the right edge) * camera_x.
**              Left edge: dir - plane, center: dir, right edge: dir + plane.
** map        : the start cell, pos without its fractional part.
** delta_dist : steps from one vertical (horizontal) line to the next.
**              One step moves the ray by r->dir (point = pos + steps * dir).
**              One step moves |dir_x| cells in x, so a cell is 1 / |dir_x|.
**              If dir_x is 0, no vertical line is ever hit, so it is 1e30.
*/
static void	raycast_init_ray(t_ray *r, const t_player *p, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / WIN_W - 1;
	r->dir_x = p->dir_x + p->plane_x * camera_x;
	r->dir_y = p->dir_y + p->plane_y * camera_x;
	r->map_x = (int)p->pos_x;
	r->map_y = (int)p->pos_y;
	r->delta_dist_x = 1e30;
	if (r->dir_x != 0)
		r->delta_dist_x = fabs(1 / r->dir_x);
	r->delta_dist_y = 1e30;
	if (r->dir_y != 0)
		r->delta_dist_y = fabs(1 / r->dir_y);
}

/*
** Before the DDA, sets the step direction and the steps to the first line.
** step      : direction between cells: +1 if dir is positive, else -1.
** side_dist : steps from the start to the first vertical (horizontal) line.
**             Cell map spans map .. map + 1, so its left (top) line is map
**             and its right (bottom) line is map + 1.
**             Going right (down): (map + 1 - pos) cells to that line.
**             Going left (up): (pos - map) cells to that line.
**             Multiplying the cells by delta_dist gives the steps.
*/
static void	raycast_init_step(t_ray *r, const t_player *p)
{
	r->step_x = 1;
	r->side_dist_x = (r->map_x + 1.0 - p->pos_x) * r->delta_dist_x;
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (p->pos_x - r->map_x) * r->delta_dist_x;
	}
	r->step_y = 1;
	r->side_dist_y = (r->map_y + 1.0 - p->pos_y) * r->delta_dist_y;
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (p->pos_y - r->map_y) * r->delta_dist_y;
	}
}

/*
** Until the ray enters a wall cell, crosses one line at a time,
** whichever of the vertical and horizontal lines comes first.
** side_dist : at which step the next vertical (horizontal) line is crossed.
**             The smaller one is crossed, moving to the next cell,
**             and is then advanced to the line one cell further.
** side      : 0 if the last line crossed is vertical (east/west face),
**             1 if it is horizontal (north/south face).
** The map is closed by walls, so every ray stops at some wall.
*/
static void	raycast_run_dda(t_ray *r, char **map)
{
	while (map[r->map_y][r->map_x] != '1')
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
	}
}

/*
** From the current position and direction, finds what is seen in
** column x of the screen and how far away it is.
** Input  : the player (pos, dir, plane), the map, the screen column x
** Output : r->map_x, r->map_y : the wall cell that was hit
**          r->side            : the face hit (0: east/west, 1: north/south)
**          r->perp_dist       : perpendicular distance to the wall
**                               (from the camera plane: no fisheye)
** perp_dist : steps to the last line crossed. side_dist is already at
**             the next line, so it goes back one cell (delta_dist).
**             p->dir has length 1, so every ray moves 1 forward per step,
**             which makes the steps the forward (perpendicular) distance.
** Right next to a wall, perp_dist gets close to 0 and would break the
** division for the wall height, so it is at least 1e-4.
** Reference: https://lodev.org/cgtutor/raycasting.html
*/
void	raycast_cast(t_ray *r, const t_player *p, char **map, int x)
{
	raycast_init_ray(r, p, x);
	raycast_init_step(r, p);
	raycast_run_dda(r, map);
	if (r->side == 0)
		r->perp_dist = r->side_dist_x - r->delta_dist_x;
	else
		r->perp_dist = r->side_dist_y - r->delta_dist_y;
	if (r->perp_dist < 1e-4)
		r->perp_dist = 1e-4;
}
