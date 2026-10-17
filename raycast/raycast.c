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
** x 列目のレイの向きと、スタート地点を決める。
** camera_x   : 画面の列を -1（左端）〜 +1（右端）に直したもの。
**              x は 0 〜 WIN_W - 1 なので、2 * x / WIN_W で 0 〜 2 にしてから 1 を引く。
** r->dir     : レイの向き。プレイヤーの向き p->dir（目から画面の真ん中まで）に、
**              p->plane（画面の真ん中から右端まで）を camera_x 倍して足す。
**              左端は dir - plane、真ん中は dir、右端は dir + plane になる。
** map        : スタートのマス。pos の小数を切り捨てたもの。
** delta_dist : 縦線（横線）から次の縦線（横線）まで何歩かかるか。
**              「1歩」はレイを r->dir 1つぶん進めること（レイ上の点 = pos + 歩数 * r->dir）。
**              1歩で x 方向に |dir_x| マス進むので、1マスぶんは 1 / |dir_x| 歩。
**              dir_x が 0 だと縦線には届かないので、とても大きい値（1e30）にしておく。
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
** DDA を始める前に、x と y それぞれの進む向きと、最初の線までの歩数を決める。
** step      : マスを進む向き。dir が正なら +1、負なら -1。
** side_dist : スタートから最初の縦線（横線）まで何歩か。
**             マス map は map 〜 map + 1 の範囲なので、左（上）の線は map、右（下）の線は map + 1。
**             右（下）に進むなら、右（下）の線まで (map + 1 - pos) マス。
**             左（上）に進むなら、左（上）の線まで (pos - map) マス。
**             このマス数に、1マスぶんの歩数 delta_dist をかけて歩数にする。
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
** レイが壁のマスに入るまで、縦線と横線のうち先に越えるほうを1本ずつ越えていく。
** side_dist : 次の縦線（横線）を越えるのは何歩目か。
**             小さいほうの線を越えて、隣のマスに移る。
**             越えたら、さらに次の線（1マス先）の歩数に進めておく。
** side      : 最後に越えたのが縦線なら 0（東西の面）、横線なら 1（南北の面）。
** マップは壁で閉じているので、どの向きのレイも必ずどこかの壁で止まる。
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
** 今の位置と向きから、画面の x 列目に何がどれだけの距離に見えるかを求める。
** 入力 : プレイヤー（pos, dir, plane）、マップ、画面の列 x
** 結果 : r->map_x, r->map_y : 当たった壁のマス
**        r->side            : 当たった面（0: 東西の面、1: 南北の面）
**        r->perp_dist       : 壁までの垂直距離（カメラ平面からの距離。魚眼にならない）
** perp_dist : 最後に越えた線までの歩数。side_dist は次の線まで進めてあるので、
**             1マスぶん（delta_dist）戻す。
**             p->dir の長さが 1 なので、どのレイも1歩で前に 1 進む。
**             だから歩数がそのまま前方向の距離（垂直距離）になる。
** 壁にぴったりくっつくと perp_dist が 0 に近くなり、壁の高さを求める割り算が
** 壊れるから、下限を 1e-4 にしておく。
** 参考: https://lodev.org/cgtutor/raycasting.html
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
