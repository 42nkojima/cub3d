/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 02:17:05 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/10 17:45:57 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_error.h"
#include "libft.h"
#include "render.h"

int	main(void)
{
	t_vars	v;

	ft_bzero(&v, sizeof(v));
	v.width = 6;
	v.height = 5;
	v.direction = NORTH;
	v.col = 4;
	v.row = 3;
	v.ceiling_color = 0x87CEEB;
	v.floor_color = 0x444444;
	if (!render_run(&v))
		handle_error(&v, "failed to open window", NULL);
	return (0);
}
