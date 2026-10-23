/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 08:44:12 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/23 08:56:37 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"

static int	map_line_len(char *line)
{
	int	len;

	len = 0;
	while (line[len] != '\0' && line[len] != '\n')
		len++;
	return (len);
}

static int	map_width(t_list *list)
{
	int	width;

	width = 0;
	while (list)
	{
		if (map_line_len(list->content) > width)
			width = map_line_len(list->content);
		list = list->next;
	}
	return (width);
}

static char	*pad_line(char *line, int width)
{
	char	*row;

	row = malloc(width + 1);
	if (!row)
		return (NULL);
	ft_memset(row, ' ', width);
	ft_memcpy(row, line, map_line_len(line));
	row[width] = '\0';
	return (row);
}

bool	convert_list_to_array(t_vars *vars, t_list *list)
{
	int	i;

	if (!list)
		return (false);
	vars->map = ft_calloc(vars->height + 1, sizeof(*vars->map));
	if (!vars->map)
		return (false);
	vars->width = map_width(list);
	i = 0;
	while (list)
	{
		vars->map[i] = pad_line(list->content, vars->width);
		if (!vars->map[i])
			return (false);
		list = list->next;
		i++;
	}
	return (true);
}
