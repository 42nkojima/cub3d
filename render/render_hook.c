/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 12:00:00 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/10 16:17:32 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_cleaner.h"
#include "mlx.h"
#include "render.h"
#include <X11/X.h>
#include <X11/keysym.h>

static int	render_on_close(t_vars *v)
{
	exit_game(v);
	return (0);
}

static int	render_on_key(int keysym, t_vars *v)
{
	if (keysym == XK_Escape)
		render_on_close(v);
	return (0);
}

void	render_set_hooks(t_vars *v)
{
	mlx_hook(v->win, KeyPress, KeyPressMask, render_on_key, v);
	mlx_hook(v->win, DestroyNotify, StructureNotifyMask, render_on_close, v);
}
