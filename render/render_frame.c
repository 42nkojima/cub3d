/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 17:51:58 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/10 17:54:46 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "render.h"

/*
** Writes color to pixel (x, y) of the image.
** addr points to the first pixel, and each row is line_len bytes long.
**   y * line_len   : move to the start of row y
**                    (use line_len, not WIN_W * 4, since rows may be padded)
**   x * (bpp / 8)  : move x pixels within the row (bpp is in bits)
** dst is a char * to count in bytes, so cast it to write all 4 bytes at once.
** Pixels outside the screen are ignored (walls can overflow when very close).
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
