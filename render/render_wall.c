/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 17:39:11 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/23 07:30:34 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "raycast.h"
#include "render.h"
#include <math.h>

/*
** Picks the texture for the face the ray hit.
** side == 1: a horizontal line was crossed (north/south face),
** side == 0: a vertical line was crossed (east/west face).
** A ray going north (step_y < 0) gets NO, south SO, west WE, east EA:
** NO goes on the walls seen when facing north.
*/
static t_dir	render_pick_tex(const t_ray *r)
{
	if (r->side == 1 && r->step_y < 0)
		return (NORTH);
	if (r->side == 1)
		return (SOUTH);
	if (r->step_x < 0)
		return (WEST);
	return (EAST);
}

/*
** Picks the texture column from where the wall was hit (wall_x).
** Hit point = pos + perp_dist * dir
** (see raycast_cast for why the steps are the distance).
** wall_x : y of the hit point on a vertical line, x on a horizontal one.
**          Its fractional part is the position in the cell (0 to 1),
**          and multiplying it by the width gives the column.
** Facing south or west, the coordinate decreases from left to right,
** which would mirror the texture, so the column is counted from the right.
*/
static int	render_tex_x(const t_player *p, const t_ray *r, int tex_w)
{
	double	wall_x;
	int		tex_x;

	if (r->side == 0)
		wall_x = p->pos_y + r->perp_dist * r->dir_y;
	else
		wall_x = p->pos_x + r->perp_dist * r->dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex_w);
	if ((r->side == 0 && r->dir_x < 0) || (r->side == 1 && r->dir_y > 0))
		tex_x = tex_w - tex_x - 1;
	return (tex_x);
}

static int	render_get_pixel(const t_img *tex, int x, int y)
{
	char	*src;

	src = tex->addr + y * tex->line_len + x * (tex->bpp / 8);
	return (*(unsigned int *)src);
}

/*
** Draws column x by stretching the texture of the face the ray hit.
** line_h : wall height: the screen height at distance 1, half at 2.
** top    : top edge of the wall, negative when it goes above the screen.
**          That part is not drawn but sets where the texture starts.
** texture y : (y - top), the pixel from the top of the wall, as a ratio
**             of the wall height, times the texture height. line_h can be
**             very large, so double is used to avoid an int overflow.
*/

static void	render_draw_column(t_vars *v, int x, const t_ray *r)
{
	t_img	*tex;
	int		tex_x;
	int		line_h;
	int		top;
	int		y;

	tex = &v->tex[render_pick_tex(r)];
	tex_x = render_tex_x(&v->player, r, tex->w);
	line_h = (int)(WIN_H / r->perp_dist);
	top = WIN_H / 2 - line_h / 2;
	y = top;
	if (y < 0)
		y = 0;
	while (y < WIN_H && y < top + line_h)
	{
		render_put_pixel(&v->img, x, y, render_get_pixel(tex, tex_x, (int)((y
						- top) * (double)tex->h / line_h)));
		y++;
	}
}

/*
** Casts one ray per column, from left to right, and draws the walls.
*/
void	render_draw_walls(t_vars *v)
{
	t_ray	r;
	int		x;

	x = 0;
	while (x < WIN_W)
	{
		raycast_cast(&r, &v->player, v->map, x);
		render_draw_column(v, x, &r);
		x++;
	}
}
