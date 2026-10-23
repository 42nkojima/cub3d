/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:15:44 by tmase             #+#    #+#             */
/*   Updated: 2026/10/17 17:24:15 by tmase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

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

void	clean_all_newlines(t_vars *vars)
{
	if (!vars)
		return ;
	trim_newline(vars->tex_path[NORTH]);
	trim_newline(vars->tex_path[SOUTH]);
	trim_newline(vars->tex_path[WEST]);
	trim_newline(vars->tex_path[EAST]);
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

void	setup_vars(t_vars *vars)
{
	ft_bzero(vars, sizeof(*vars));
	vars->ceiling_color = -1;
	vars->floor_color = -1;
	vars->col = -1;
}

bool	parse(int ac, char **av, t_vars *vars)
{
	int	fd;

	if (!check_args(ac, av))
		return (false);
	setup_vars(vars);
	fd = open(av[1], O_RDONLY);
	if (!fd)
		return (false);
	if (parse_config(fd, vars) && parse_map(fd, vars))
	{
		clean_all_newlines(vars);
		close(fd);
		return (true);
	}
	return (false);
}
