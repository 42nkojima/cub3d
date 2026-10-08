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

static bool	render_open_window(t_vars *v)
{
	v->mlx = mlx_init();
	if (!v->mlx)
		return (false);
	v->win = mlx_new_window(v->mlx, WIN_W, WIN_H, "cub3D");
	if (!v->win)
	{
		mlx_destroy_display(v->mlx);
		free(v->mlx);
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

static void	render_put_info(const t_vars *v)
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
	mlx_string_put(v->mlx, v->win, 20, 20, 0xFFFFFF, buf);
}

bool	render_run(t_vars *v)
{
	if (!render_open_window(v))
		return (false);
	render_put_info(v);
	mlx_loop(v->mlx);
	return (true);
}
