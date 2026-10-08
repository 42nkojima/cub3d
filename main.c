/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 02:17:05 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/04 07:11:52 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	main(void)
{
	t_vars	v;

	v.width = 6;
	v.height = 5;
	v.direction = NORTH;
	v.col = 4;
	v.row = 3;
	if (!render_run(&v))
		return (1);
	return (0);
}
