/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 17:39:11 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/11 17:46:06 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "raycast.h"
#include "render.h"

/*
** x 列目に、レイの結果から壁の縦線を描く。
** line_h : 壁の高さ。距離 1 で画面の高さぴったり、距離 2 で半分になる。
** start, end : 画面の真ん中を中心に、上下に line_h / 2 ずつ伸ばした範囲。
**              壁に近いと画面からはみ出すので、画面の端で止める。
** color : 東西の面 (side == 0) と南北の面 (side == 1) で色を変える。
*/
static void	render_draw_column(t_vars *v, int x, const t_ray *r)
{
	int	line_h;
	int	start;
	int	end;
	int	color;

	line_h = (int)(WIN_H / r->perp_dist);
	start = WIN_H / 2 - line_h / 2;
	end = WIN_H / 2 + line_h / 2;
	if (start < 0)
		start = 0;
	if (end >= WIN_H)
		end = WIN_H - 1;
	color = WALL_COLOR_NS;
	if (r->side == 0)
		color = WALL_COLOR_EW;
	while (start <= end)
	{
		render_put_pixel(&v->img, x, start, color);
		start++;
	}
}

/*
** 画面の左端から右端まで、1列ずつレイを飛ばして壁の縦線を描く。
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
