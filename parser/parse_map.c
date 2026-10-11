/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 20:19:38 by tmase             #+#    #+#             */
/*   Updated: 2026/10/11 20:19:54 by tmase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

t_list	*ft_lstnew(char *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst= lst->next;
	return (lst);
}

bool	line_to_list(char *line, t_list **list)
{
	t_list	*new_node;
	t_list	*last;

	new_node = ft_lstnew(line);
	if (!new_node)
		return (false);
	if (*list == NULL)
		*list = new_node;
	else
	{
		last = ft_lstlast(*list);
		last->next = new_node;
	}
	return (true);
}

bool	check_line(t_vars *vars, char *line)
{
	int	i;

	i = 0;
>>>>>>> Stashed changes
}

bool	convert_list_to_array(t_vars *vars, t_list *list)
{
	t_list	*current;
	int		i;
	size_t	len;

	if (!list)
		return (false);
	vars->width = 0;
	current = list;
	while (current)
	{
		len = ft_strlen(current->content);
		if (len > 0 && current->content[len - 1] == '\n')
			len--;
		if (len > vars->width)
			vars->width = len;
		current = current->next;
	}
	
}

bool	parse_map(int fd, t_vars *vars)
{
	char	*line;
	t_list	*list;

	list = NULL;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (is_empty_line(line))
		{
			if (list == NULL)
			{
				free(line);
				continue;
			}
			else
				return (free(line), false);
		}
		if (!check_line(vars, line))
			return (free(line), false);
		if (!line_to_list(line, &list))
			return (free(line), false);
		vars->height++;
	}
	if (!vars->direction)
		return (false);
	if (!convert_list_to_array(vars, list))
		return (false);
	clear_all_list(list);
	return (true);
}
