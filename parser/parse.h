/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 13:27:00 by tmase             #+#    #+#             */
/*   Updated: 2026/10/25 14:53:13 by tmase            ###   ########.fr       */
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

bool	parse_config(int fd, t_vars *v);
bool	parse_map(int fd, t_vars *v);
void	parse(int ac, char **av, t_vars *v);
bool	is_empty_line(char *line);
t_list	*ft_lstnew(char *content);
t_list	*ft_lstlast(t_list *lst);
void	clear_all_list(t_list *list);
bool	line_to_list(char *line, t_list **list);
bool	convert_list_to_array(t_vars *v, t_list *list);
bool	is_map_closed(t_vars *v);
bool	set_color(t_vars *v, char *line, char c);
bool	set_texture(t_vars *v, t_dir dir, char *path);

#endif
