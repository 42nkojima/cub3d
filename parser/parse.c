/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:15:44 by tmase             #+#    #+#             */
/*   Updated: 2026/10/25 14:54:59 by tmase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include "cub_error.h"

static void	trim_newline(char *str)
{
	size_t	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r'))
	{
		str[len - 1] = '\0';
		len--;
	}
}

void	clean_all_newlines(t_vars *v)
{
	if (!v)
		return ;
	trim_newline(v->tex_path[NORTH]);
	trim_newline(v->tex_path[SOUTH]);
	trim_newline(v->tex_path[WEST]);
	trim_newline(v->tex_path[EAST]);
}

bool	check_args(int ac, char **av)
{
	size_t	len;

	if (ac != 2)
		return (false);
	if (!av[1])
		return (false);
	len = ft_strlen(av[1]);
	if (len < 4 || ft_strncmp(av[1] + len - 4, ".cub", 4) != 0)
		return (false);
	return (true);
}

void	setup_vars(t_vars *v)
{
	ft_bzero(v, sizeof(*v));
	v->ceiling_color = -1;
	v->floor_color = -1;
	v->col = -1;
}

void	parse(int ac, char **av, t_vars *v)
{
	int	fd;

	setup_vars(v);
	if (!check_args(ac, av))
		handle_error(v, "args error", NULL);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		handle_error(v, "Failed to open file", NULL);
	if (!parse_config(fd, v))
	{
		close(fd);
		handle_error(v, "Invalid color code or texture path", NULL);
	}
	if (!parse_map(fd, v))
	{
		close(fd);
		handle_error(v, "Invalid map", NULL);
	}
	clean_all_newlines(v);
	close(fd);
}
