/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 12:00:00 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/11 19:23:48 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_cleaner.h"
#include "mlx.h"
#include "raycast.h"
#include "render.h"
#include <X11/X.h>
#include <X11/keysym.h>

static int	render_on_close(t_vars *v)
{
	exit_game(v);
	return (0);
}

/*
** Puts the image back when the window becomes visible again (Expose).
** The image buffer still holds the last frame, so no need to redraw.
*/
static int	render_on_expose(t_vars *v)
{
	mlx_put_image_to_window(v->mlx, v->win, v->img.ptr, 0, 0);
	return (0);
}

static int	render_on_key(int keysym, t_vars *v)
{
	if (keysym == XK_Escape)
		render_on_close(v);
	else if (keysym == XK_Left)
		raycast_rotate(&v->player, -ROT_SPEED);
	else if (keysym == XK_Right)
		raycast_rotate(&v->player, ROT_SPEED);
	else if (keysym == XK_w)
		raycast_move(&v->player, v->map, v->player.dir_x, v->player.dir_y);
	else if (keysym == XK_s)
		raycast_move(&v->player, v->map, -v->player.dir_x, -v->player.dir_y);
	else if (keysym == XK_d)
		raycast_move(&v->player, v->map, -v->player.dir_y, v->player.dir_x);
	else if (keysym == XK_a)
		raycast_move(&v->player, v->map, v->player.dir_y, -v->player.dir_x);
	else
		return (0);
	render_frame(v);
	return (0);
}

void	render_set_hooks(t_vars *v)
{
	mlx_hook(v->win, KeyPress, KeyPressMask, render_on_key, v);
	mlx_hook(v->win, DestroyNotify, StructureNotifyMask, render_on_close, v);
	mlx_hook(v->win, Expose, ExposureMask, render_on_expose, v);
}
