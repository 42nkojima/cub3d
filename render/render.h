/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 02:25:00 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/04 02:36:17 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <stdbool.h>

# define WIN_W 640
# define WIN_H 480

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}			t_mlx;

bool		render_run(t_mlx *m);

#endif
