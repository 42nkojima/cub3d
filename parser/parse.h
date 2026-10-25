/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 13:27:00 by tmase             #+#    #+#             */
/*   Updated: 2026/10/25 13:42:13 by nkojima          ###   ########.fr       */
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
bool	parse(int ac, char **av, t_vars *vars);
bool	is_empty_line(char *line);
t_list	*ft_lstnew(char *content);
t_list	*ft_lstlast(t_list *lst);
void	clear_all_list(t_list *list);
bool	line_to_list(char *line, t_list **list);
bool	convert_list_to_array(t_vars *vars, t_list *list);
bool	is_map_closed(t_vars *vars);
bool	set_color(t_vars *vars, char *line, char c);

#endif
