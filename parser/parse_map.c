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

typedef	struct s_list {
	char	*line;
	t_list	*prev;
	t_list	*next;
}				t_list;

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

	
	while ((line = get_next_line(fd)) != NULL)
	{
		if (is_empty_line(line))
		{
			free(line);
			continue;
		}
		if (!map_to_list(vars, line, list))
		{
			free(line);
			return (false);
		}
	}
	if (!convert_list_to_array(vars, list))
		return (false);
	return (true);
}