/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 16:24:38 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/11 17:59:09 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

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
