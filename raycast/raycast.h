/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 16:24:41 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/11 18:53:32 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "cub.h"

# define PLANE_LEN 0.66
# define ROT_SPEED 0.05
# define MOVE_SPEED 0.1

// Kept here, not in cub.h: render only uses it and needs no details.
typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_dist;
}			t_ray;

void		raycast_init_player(t_vars *v);
void		raycast_rotate(t_player *p, double angle);
void		raycast_cast(t_ray *r, const t_player *p, char **map, int x);
void		raycast_move(t_player *p, char **map, double dx, double dy);

#endif