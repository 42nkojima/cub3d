/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 13:27:00 by tmase             #+#    #+#             */
/*   Updated: 2026/10/04 16:54:07 by tmase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include "cub.h"
#include <stdbool.h>
#include <fcntl.h>

bool	parse_config(int fd, t_vars *vars);
bool	parse_map(int fd, t_vars *vars);

#endif