/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 20:19:38 by tmase             #+#    #+#             */
/*   Updated: 2026/10/17 20:13:28 by tmase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

static int	line_to_direction(char c)
{
	if (c == 'N')
		return (NORTH);
	else if (c == 'S')
		return (SOUTH);
	else if (c == 'E')
		return (EAST);
	else
		return (WEST);
}

static bool	check_line(t_vars *vars, char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (false);
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			if (vars->col != -1)
				return (false);
			vars->row = vars->height;
			vars->col = i;
			vars->direction = line_to_direction(line[i]);
		}
		i++;
	}
	return (true);
}

static bool	convert_list_to_array(t_vars *vars, t_list *list)
{
	t_list	*cur;
	int		i;

	if (!list)
		return (false);
	vars->map = malloc(sizeof(char *) * (vars->height + 1));
	if (!vars->map)
		return (false);
	cur = list;
	i = 0;
	while (cur)
	{
		if ((int)ft_strlen(cur->content) > vars->width)
			vars->width = ft_strlen(cur->content);
		vars->map[i] = ft_strdup(cur->content);
		if (!vars->map[i])
			return (false);
		cur = cur->next;
		i++;
	}
	vars->map[i] = NULL;
	return (true);
}

static bool	process_line(t_vars *vars, t_list **list, char *line)
{
	if (is_empty_line(line))
	{
		if (*list == NULL)
		{
			free(line);
			return (true);
		}
		return (free(line), false);
	}
	if (!check_line(vars, line) || !line_to_list(line, list))
		return (free(line), false);
	vars->height++;
	return (true);
}

bool	parse_map(int fd, t_vars *vars)
{
	char	*line;
	t_list	*list;

	list = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!process_line(vars, &list, line))
		{
			clear_all_list(list);
			return (false);
		}
		line = get_next_line(fd);
	}
	if (vars->col == -1 || !convert_list_to_array(vars, list))
	{
		clear_all_list(list);
		return (false);
	}
	clear_all_list(list);
	return (true);
}
