/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 19:45:08 by tmase             #+#    #+#             */
/*   Updated: 2026/10/17 19:55:26 by tmase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

bool	is_empty_line(char *line)
{
	if (line[0] == '\n')
		return (true);
	return (false);
}

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
		lst = lst->next;
	return (lst);
}

void	clear_all_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list->next;
		if (list->content)
			free(list->content);
		free(list);
		list = tmp;
	}
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
