/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 02:17:05 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/10 18:00:06 by tmase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_error.h"
#include "libft.h"
#include "render.h"
#include "parse.h"

int	main(void)
{
	t_vars	v;

	ft_bzero(&v, sizeof(v));
	v.ceiling_color = -1;
	v.floor_color = -1;
	v.width = 6;
	v.height = 5;
	v.direction = NORTH;
	v.col = 4;
	v.row = 3;
	if (!render_run(&v))
		handle_error(&v, "failed to open window", NULL);
	return (0);
}
