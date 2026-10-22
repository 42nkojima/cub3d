/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 13:27:00 by tmase             #+#    #+#             */
/*   Updated: 2026/10/17 20:09:10 by tmase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "cub.h"
# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

bool	parse_config(int fd, t_vars *vars);
bool	parse_map(int fd, t_vars *vars);
bool	parse(char *filepath, t_vars *vars);
bool	is_empty_line(char *line);
t_list	*ft_lstnew(char *content);
t_list	*ft_lstlast(t_list *lst);
void	clear_all_list(t_list *list);
bool	line_to_list(char *line, t_list **list);

#endif
