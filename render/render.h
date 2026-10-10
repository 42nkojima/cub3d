/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 02:25:00 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/10 17:47:27 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "cub.h"
# include <stdbool.h>

# define WIN_W 640
# define WIN_H 480

bool	render_run(t_vars *v);
void	render_frame(t_vars *v);
void	render_put_pixel(t_img *img, int x, int y, int color);

#endif
