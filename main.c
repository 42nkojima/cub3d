/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 02:17:05 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/11 19:25:26 by tmase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_error.h"
#include "libft.h"
#include "render.h"
#include "parse.h"

static char	**make_test_map(void)
{
	char	*map;

	map = "1111111111\n"
		"1000000001\n"
		"1001100001\n"
		"1000000001\n"
		"1000010001\n"
		"1000000001\n"
		"1111111111";
	return (ft_split(map, '\n'));
}

int	main(void)
{
	t_vars	v;

	ft_bzero(&v, sizeof(v));
	v.ceiling_color = -1;
	v.floor_color = -1;
	v.map = make_test_map();
	if (!v.map)
		handle_error(&v, "failed to allocate map", NULL);
	v.width = 10;
	v.height = 7;
	v.direction = NORTH;
	v.col = 4;
	v.row = 5;
	v.ceiling_color = 0x87CEEB;
	v.floor_color = 0x444444;
	if (!render_run(&v))
		handle_error(&v, "failed to open window", NULL);
	return (0);
}
