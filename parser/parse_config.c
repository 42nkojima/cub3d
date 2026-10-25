/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 20:20:07 by tmase             #+#    #+#             */
/*   Updated: 2026/10/25 13:39:31 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

bool	parse_element_line(char *line, t_vars *vars)
{
	if (line[0] == 'N' && line[1] == 'O' && !vars->tex_path[NORTH])
		vars->tex_path[NORTH] = ft_strdup(line + 3);
	else if (line[0] == 'S' && line[1] == 'O' && !vars->tex_path[SOUTH])
		vars->tex_path[SOUTH] = ft_strdup(line + 3);
	else if (line[0] == 'W' && line[1] == 'E' && !vars->tex_path[WEST])
		vars->tex_path[WEST] = ft_strdup(line + 3);
	else if (line[0] == 'E' && line[1] == 'A' && !vars->tex_path[EAST])
		vars->tex_path[EAST] = ft_strdup(line + 3);
	else if (line[0] == 'F' && vars->floor_color == -1)
		return (set_color(vars, line + 2, 'f'));
	else if (line[0] == 'C' && vars->ceiling_color == -1)
		return (set_color(vars, line + 2, 'c'));
	else
		return (false);
	return (true);
}

bool	is_all_config_set(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!vars->tex_path[i])
			return (false);
		i++;
	}
	if (vars->floor_color == -1 || vars->ceiling_color == -1)
		return (false);
	return (true);
}

bool	parse_config(int fd, t_vars *vars)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_empty_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!parse_element_line(line, vars))
		{
			free(line);
			return (false);
		}
		free(line);
		if (is_all_config_set(vars))
			break ;
		line = get_next_line(fd);
	}
	if (!is_all_config_set(vars))
		return (false);
	return (true);
}
