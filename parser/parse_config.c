/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 20:20:07 by tmase             #+#    #+#             */
/*   Updated: 2026/10/23 11:29:54 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	free_split(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

bool	set_color(t_vars *vars, char *line, char c)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	int		color;

	rgb = ft_split(line, ',');
	if (!rgb)
		return (false);
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_split(rgb), false);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_split(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (false);
	color = (r << 16 | g << 8 | b);
	if (c == 'c')
		vars->ceiling_color = color;
	else if (c == 'f')
		vars->floor_color = color;
	return (true);
}

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
