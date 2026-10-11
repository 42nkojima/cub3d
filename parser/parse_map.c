/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:15:51 by tmase             #+#    #+#             */
/*   Updated: 2026/10/11 19:21:31 by tmase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

bool	map_to_list(t_vars *vars, char *line, t_list *list)
{
}

bool	convert_list_to_array(t_vars *vars, t_list *list)
{
}

bool	parse_map(int fd, t_vars *vars)
{
	char	*line;
	t_list	*list;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_empty_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!map_to_list(vars, line, list))
		{
			free(line);
			return (false);
		}
		line = get_next_line(fd);
	}
	if (!convert_list_to_array(vars, list))
		return (false);
	return (true);
}
