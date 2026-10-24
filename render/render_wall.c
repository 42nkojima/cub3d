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
** レイが当たった面に貼るテクスチャを選ぶ。
** side == 1 は横線 (南北の面)、side == 0 は縦線 (東西の面) を越えて当たった。
** レイが北に進んでいる (step_y < 0) なら NO、 南なら SO、西なら WE、東なら EA。
** 「北を向いた時に見える壁に NO を貼る」という決め方
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
** 壁のどこに当たったか (wall_x) から、テクスチャの何列目を使うかを決める。
** 当たった点 = pos + perp_dist * dir (歩数がそのまま距離なのは raycast_cast を参照)
** wall_x : 縦線に当たったなら y 座標、横線なら x 座標。小数部分だけ取ると、
**          マスの中のどこか (0~1) になる。これに幅をかけて列にする。
** 南と西を向いているときは、画面の左から右に行くと座標が小さくなっていく。
** そのままだとテクスチャが左右反転するので、右端から数え直す。
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
** x 列目に、レイが当たった面のテクスチャを縦に引き伸ばして描く。
** line_h : 壁の高さ。距離 1 で画面の高さぴったり、距離 2 で半分になる。
** top    : 壁の上端。壁に近いと画面の上にはみ出してマイナスになる。
**          はみ出した分は描かないけど、テクスチャのどこから描くかの計算には使う。
** テクスチャの y : 壁の上端から何ピクセル目か (y - top) を、壁の高さに対する割合にして、
**                  テクスチャの高さをかける。line_h はとても大きくなることがあるので、
**                  int の掛け算ではみ出さないように double で計算する。
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
