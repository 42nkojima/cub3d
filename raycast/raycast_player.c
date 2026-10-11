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
** マップの N・S・W・E に合わせて、プレイヤーの位置と向きを決める。
** pos   : マスの真ん中に立たせるため +0.5 する。
** dir   : t_dir の並び（NORTH, SOUTH, WEST, EAST）の順に、向きの表から選ぶ。
**         y は下に行くほど大きいので、北は (0, -1)。
** plane : dir を右に 90° 回した (-dir_y, dir_x) に、視野の広さ PLANE_LEN をかける。
**         dir と同じように回さないと、画面が左右反転したり歪んだりする。
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
** ベクトル (x, y) を angle (ラジアン) だけ回す。
** 回転の公式を使う。 https://mathlandscape.com/rotation-matrix/
** x を先に書き換えると y の計算で新しい x を使ってしまうから、元の x は取っておく。
** y は下に行くほど大きいから、angle が正だと見た目は右回りになる。
*/
static void	raycast_rotate_vec(double *x, double *y, double angle)
{
	double	old_x;

	old_x = *x;
	*x = old_x * cos(angle) - *y * sin(angle);
	*y = old_x * sin(angle) + *y * cos(angle);
}

/*
** プレイヤーの向きを angle だけ回す。
** dir と plane を同じ角度だけ回すから、長さも直角の関係も変わらず、画面が歪まない。
*/
void	raycast_rotate(t_player *p, double angle)
{
	raycast_rotate_vec(&p->dir_x, &p->dir_y, angle);
	raycast_rotate_vec(&p->plane_x, &p->plane_y, angle);
}

/*
** プレイヤーを (dx, dy) の向きに MOVE_SPEED だけ動かす。動いた先が壁のマスなら動かない。
** 壁のマスに入ると DDA のスタート地点が壁になって描画が壊れ、マップの外に出ると落ちてしまうため。
** x と y を別々にチェックするから、斜めに壁にぶつかっても壁に沿って滑れる。
** マップが壁で閉じていることはパーサーが保証するので、'1' かどうかだけ見ればいい。
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
