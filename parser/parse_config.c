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

/*
** line が「id → スペース1つ以上 → 値」の形なら、値の先頭を返す。違えば NULL。
**   OK : "NO ./a.xpm"   "NO     ./a.xpm"
**   NG : "NOX ./a.xpm"  "NO./a.xpm"  "NO<タブ>./a.xpm"  "NO"
** ft_strncmp は line が短くても \0 で止まるので、文字列の外は読まない。
*/
static char	*get_value(char *line, char *id)
{
	size_t	len;

	len = ft_strlen(id);
	if (ft_strncmp(line, id, len) != 0 || line[len] != ' ')
		return (NULL);
	while (line[len] == ' ')
		len++;
	return (line + len);
}

bool	parse_element_line(char *line, t_vars *vars)
{
	if (get_value(line, "NO") && !vars->tex_path[NORTH])
		return (set_texture(vars, NORTH, get_value(line, "NO")));
	else if (get_value(line, "SO") && !vars->tex_path[SOUTH])
		return (set_texture(vars, SOUTH, get_value(line, "SO")));
	else if (get_value(line, "WE") && !vars->tex_path[WEST])
		return (set_texture(vars, WEST, get_value(line, "WE")));
	else if (get_value(line, "EA") && !vars->tex_path[EAST])
		return (set_texture(vars, EAST, get_value(line, "EA")));
	else if (get_value(line, "F") && vars->floor_color == -1)
		return (set_color(vars, get_value(line, "F"), 'f'));
	else if (get_value(line, "C") && vars->ceiling_color == -1)
		return (set_color(vars, get_value(line, "C"), 'c'));
	return (false);
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
