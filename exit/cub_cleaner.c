/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_cleaner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 20:00:33 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/10 17:46:48 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_cleaner.h"
#include "mlx.h"
#include <stdlib.h>

static void	free_tex_paths(t_vars *v)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(v->tex_path[i]);
		v->tex_path[i] = NULL;
		i++;
	}
}

static void	free_map(t_vars *v)
{
	int	i;

	if (!v->map)
		return ;
	i = 0;
	while (v->map[i])
		free(v->map[i++]);
	free(v->map);
	v->map = NULL;
}

static void	destroy_mlx(t_vars *v)
{
	if (!v->mlx)
		return ;
	if (v->img.ptr)
		mlx_destroy_image(v->mlx, v->img.ptr);
	if (v->win)
		mlx_destroy_window(v->mlx, v->win);
	mlx_destroy_display(v->mlx);
	free(v->mlx);
	v->img.ptr = NULL;
	v->win = NULL;
	v->mlx = NULL;
}

void	destroy_vars(t_vars *v)
{
	free_tex_paths(v);
	free_map(v);
	destroy_mlx(v);
}
