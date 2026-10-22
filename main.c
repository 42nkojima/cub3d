/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 02:17:05 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/17 15:48:59 by tmase            ###   ########.fr       */
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
	parse("maps/good/simple.cub", &v);
	if (!render_run(&v))
		handle_error(&v, "failed to open window", NULL);
	return (0);
}
