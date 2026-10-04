/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 02:27:30 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/04 07:11:29 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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

static void	render_append_nbr(char *buf, size_t size, int n)
{
	char	*s;

	s = ft_itoa(n);
	if (!s)
		return ;
	ft_strlcat(buf, s, size);
	free(s);
}

static void	render_put_info(t_mlx *m, const t_vars *v)
{
	char	buf[64];
	char	dir[2];

	buf[0] = '\0';
	dir[0] = "NSWE"[v->direction];
	dir[1] = '\0';
	ft_strlcat(buf, "map: ", sizeof(buf));
	render_append_nbr(buf, sizeof(buf), v->width);
	ft_strlcat(buf, "x", sizeof(buf));
	render_append_nbr(buf, sizeof(buf), v->height);
	ft_strlcat(buf, "  player: ", sizeof(buf));
	ft_strlcat(buf, dir, sizeof(buf));
	ft_strlcat(buf, " (", sizeof(buf));
	render_append_nbr(buf, sizeof(buf), v->col);
	ft_strlcat(buf, ",", sizeof(buf));
	render_append_nbr(buf, sizeof(buf), v->row);
	ft_strlcat(buf, ")", sizeof(buf));
	mlx_string_put(m->mlx, m->win, 20, 20, 0xFFFFFF, buf);
}

bool	render_run(t_mlx *m, const t_vars *v)
{
	if (!render_open_window(m))
		return (false);
	render_put_info(m, v);
	mlx_loop(m->mlx);
	return (true);
}
