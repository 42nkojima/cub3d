/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 17:51:58 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/11 17:46:24 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "render.h"

/*
** Writes color at (x, y) of the image.
** addr is the start of the pixel data, and one row is line_len bytes.
**   y * line_len   : moves to the start of row y
**                    (line_len, not WIN_W * 4, as rows may be padded)
**   x * (bpp / 8)  : moves x pixels in the row (bpp is in bits)
** dst is a char * to count in bytes, so it is cast to write 4 bytes.
** Pixels off the screen are ignored (walls overflow when close).
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
	render_draw_walls(v);
	mlx_put_image_to_window(v->mlx, v->win, v->img.ptr, 0, 0);
}
