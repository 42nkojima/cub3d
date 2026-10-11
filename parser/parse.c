/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:15:44 by tmase             #+#    #+#             */
/*   Updated: 2026/10/11 20:16:32 by tmase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

bool	parse(char *filepath, t_vars *vars)
{
	int		fd;
	bool	status;

	fd = open(filepath, O_RDONLY);
	status = parse_config(fd, vars) && parse_map(fd, vars);
	close(fd);
	return (status);
}
