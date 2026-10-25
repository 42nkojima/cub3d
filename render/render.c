/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 02:27:30 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/23 06:42:01 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_error.h"
#include "mlx.h"
#include "raycast.h"
#include "render.h"

static bool	render_open_window(t_vars *v)
{
	v->mlx = mlx_init();
	if (!v->mlx)
		return (false);
	v->win = mlx_new_window(v->mlx, WIN_W, WIN_H, "cub3D");
	if (!v->win)
		return (false);
	v->img.ptr = mlx_new_image(v->mlx, WIN_W, WIN_H);
	if (!v->img.ptr)
		return (false);
	v->img.addr = mlx_get_data_addr(v->img.ptr, &v->img.bpp, &v->img.line_len,
			&v->img.endian);
	return (true);
}

static void	render_load_textures(t_vars *v)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		v->tex[i].ptr = mlx_xpm_file_to_image(v->mlx, v->tex_path[i],
				&v->tex[i].w, &v->tex[i].h);
		if (!v->tex[i].ptr)
			handle_error(v, "failed to load texture", v->tex_path[i]);
		v->tex[i].addr = mlx_get_data_addr(v->tex[i].ptr, &v->tex[i].bpp,
				&v->tex[i].line_len, &v->tex[i].endian);
		i++;
	}
}

bool	render_run(t_vars *v)
{
	if (!render_open_window(v))
		return (false);
	render_load_textures(v);
	raycast_init_player(v);
	render_frame(v);
	render_set_hooks(v);
	mlx_loop(v->mlx);
	return (true);
}
