/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 02:25:00 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/11 17:38:53 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "cub.h"
# include <stdbool.h>

# define WALL_COLOR_EW 0xC04030
# define WALL_COLOR_NS 0x3060C0

bool	render_run(t_vars *v);
void	render_frame(t_vars *v);
void	render_draw_walls(t_vars *v);
void	render_put_pixel(t_img *img, int x, int y, int color);
void	render_set_hooks(t_vars *v);

#endif
