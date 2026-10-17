/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:15:44 by tmase             #+#    #+#             */
/*   Updated: 2026/10/17 15:50:43 by tmase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

static void	trim_newline(char *str)
{
	size_t	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r'))
	{
		str[len - 1] = '\0';
		len--;
	}
}

void	clean_all_newlines(t_vars *vars)
{
	int	i;

	if (!vars)
		return ;
	trim_newline(vars->tex_path[NORTH]);
	trim_newline(vars->tex_path[SOUTH]);
	trim_newline(vars->tex_path[WEST]);
	trim_newline(vars->tex_path[EAST]);
	if (vars->map)
	{
		i = 0;
		while (vars->map[i])
		{
			trim_newline(vars->map[i]);
			i++;
		}
	}
}

void	print_map_debug(t_vars *vars)
{
	int	i;

	if (!vars || !vars->map)
	{
		printf("[DEBUG] Map is NULL\n");
		return ;
	}
	printf("=== MAP DEBUG INFO ===\n");
	printf("Height   : %d\n", vars->height);
	printf("Width    : %d\n", vars->width);
	printf("Player   : %c at (col/y: %d, row/x: %d)\n",
		vars->direction, vars->col, vars->row);
	printf("----------------------\n");
	i = 0;
	while (vars->map[i])
	{
		printf("[%02d] \"%s\"\n", i, vars->map[i]);
		i++;
	}
	printf("======================\n");
}

void	test_parse(t_vars *vars)
{
	printf("%s\n%s\n%s\n%s\n", vars->tex_path[NORTH],
		vars->tex_path[SOUTH], vars->tex_path[WEST], vars->tex_path[EAST]);
	printf("C: %d\nF: %d\n", vars->ceiling_color, vars->floor_color);
	printf("OK!!!!!!!!");
	printf("\n======================\n");
	print_map_debug(vars);
}

bool	parse(char *filepath, t_vars *vars)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (parse_config(fd, vars) && parse_map(fd, vars))
	{
		clean_all_newlines(vars);
		test_parse(vars);
		close(fd);
		return (true);
	}
	return (false);
}
