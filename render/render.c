/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 02:27:30 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/04 02:44:54 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "render.h"
#include <stdlib.h>

static bool	render_open_window(t_mlx *m)
{
	m->mlx = mlx_init();
	if (!m->mlx)
		return (false);
	m->win = mlx_new_window(m->mlx, WIN_W, WIN_H, "cub3D");
	if (!m->win)
	{
		mlx_destroy_display(m->mlx);
		free(m->mlx);
		return (false);
	}
	return (true);
}

bool	render_run(t_mlx *m)
{
	if (!render_open_window(m))
		return (false);
	mlx_loop(m->mlx);
	return (true);
}
