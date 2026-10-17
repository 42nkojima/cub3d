/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 02:17:05 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/17 17:09:16 by tmase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_error.h"
#include "libft.h"
#include "render.h"
#include "parse.h"

int	main(int ac, char **av)
{
	t_vars	v;

	if (!parse(ac, av, &v))
		return (1);
	if (!render_run(&v))
		handle_error(&v, "failed to open window", NULL);
	return (0);
}
