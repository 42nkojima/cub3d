/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 17:51:58 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/10 18:06:39 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "render.h"

/*
** 画像の (x, y) に色を書き込む。
** addr はピクセルデータの先頭で、1行ぶんのバイト数が line_len。
**   y * line_len   : y 行目の先頭まで進む
**                    （行末に余白が入ることがあるので WIN_W * 4 ではなく line_len）
**   x * (bpp / 8)  : その行の中で x ピクセルぶん進む（bpp はビット数なので 8 で割る）
** dst はバイト単位で数えるために char * なので、4 バイトまとめて書くときはキャストする。
** 画面外は書き込まずに無視する（壁に近づいたときのはみ出し対策）。
*/
void	render_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = img->addr + y * img->line_len + x * (img->bpp / 8);
	*(unsigned int *)dst = color;
}

static void	render_draw_background(t_vars *v)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			if (y < WIN_H / 2)
				render_put_pixel(&v->img, x, y, v->ceiling_color);
			else
				render_put_pixel(&v->img, x, y, v->floor_color);
			x++;
		}
		y++;
	}
}

void	render_frame(t_vars *v)
{
	render_draw_background(v);
	mlx_put_image_to_window(v->mlx, v->win, v->img.ptr, 0, 0);
}
