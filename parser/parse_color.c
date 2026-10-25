/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 13:38:32 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/25 13:42:53 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	free_split(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

bool	set_color(t_vars *vars, char *line, char c)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	int		color;

	rgb = ft_split(line, ',');
	if (!rgb)
		return (false);
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_split(rgb), false);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_split(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (false);
	color = (r << 16 | g << 8 | b);
	if (c == 'c')
		vars->ceiling_color = color;
	else if (c == 'f')
		vars->floor_color = color;
	return (true);
}
