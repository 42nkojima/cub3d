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
** Returns the start of the value if line is "id, spaces, value",
** or NULL otherwise.
**   OK : "NO ./a.xpm"   "NO     ./a.xpm"
**   NG : "NOX ./a.xpm"  "NO./a.xpm"  "NO<tab>./a.xpm"  "NO"
** ft_strncmp stops at \0 even if line is short, so it never reads past it.
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

bool	parse_element_line(char *line, t_vars *v)
{
	if (get_value(line, "NO") && !v->tex_path[NORTH])
		return (set_texture(v, NORTH, get_value(line, "NO")));
	else if (get_value(line, "SO") && !v->tex_path[SOUTH])
		return (set_texture(v, SOUTH, get_value(line, "SO")));
	else if (get_value(line, "WE") && !v->tex_path[WEST])
		return (set_texture(v, WEST, get_value(line, "WE")));
	else if (get_value(line, "EA") && !v->tex_path[EAST])
		return (set_texture(v, EAST, get_value(line, "EA")));
	else if (get_value(line, "F") && v->floor_color == -1)
		return (set_color(v, get_value(line, "F"), 'f'));
	else if (get_value(line, "C") && v->ceiling_color == -1)
		return (set_color(v, get_value(line, "C"), 'c'));
	return (false);
}

bool	is_all_config_set(t_vars *v)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!v->tex_path[i])
			return (false);
		i++;
	}
	if (v->floor_color == -1 || v->ceiling_color == -1)
		return (false);
	return (true);
}

bool	parse_config(int fd, t_vars *v)
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
		if (!parse_element_line(line, v))
		{
			free(line);
			return (false);
		}
		free(line);
		if (is_all_config_set(v))
			break ;
		line = get_next_line(fd);
	}
	if (!is_all_config_set(v))
		return (false);
	return (true);
}
