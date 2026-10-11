/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 16:24:38 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/11 16:24:38 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

/*
** +0.5 はマスの真ん中に立たせるため
** 今は北向き固定。
TODO: #28 で direction を見て NSEW に合わせるようにする
*/
void	raycast_init_player(t_vars *v)
{
	v->player.pos_x = v->col + 0.5;
	v->player.pos_y = v->row + 0.5;
	v->player.dir_x = 0;
	v->player.dir_y = -1;
	v->player.plane_x = 0.66;
	v->player.plane_y = 0;
}
