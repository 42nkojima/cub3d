/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 13:27:00 by tmase             #+#    #+#             */
/*   Updated: 2026/10/11 20:20:57 by tmase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "cub.h"
# include <stdbool.h>
# include <fcntl.h>

typedef struct s_list
{
	char			*line;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

bool	parse_config(int fd, t_vars *vars);
bool	parse_map(int fd, t_vars *vars);
bool	is_empty_line(char *line);

#endif