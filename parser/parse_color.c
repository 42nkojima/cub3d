/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 13:38:32 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/25 15:14:30 by tmase            ###   ########.fr       */
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

/*
** 「1〜3 桁の数字」のあとに、行の終わりか文字列の終わりが来るものだけ OK。
** スペース、先頭の 0（007 など）、+ や - はエラー。
** 3桁までにしてるのは、ft_atoi で int があふれないようにするため。
*/
static bool	is_color_value(char *s)
{
	int	digits;

	digits = 0;
	while (ft_isdigit(s[digits]))
		digits++;
	if (digits == 0 || digits > 3 || (s[0] == '0' && digits > 1))
		return (false);
	return (s[digits] == '\0' || s[digits] == '\n');
}

static int	rgb_to_color(char **rgb)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r > 255 || g > 255 || b > 255)
		return (-1);
	return (r << 16 | g << 8 | b);
}

static int	count_commas(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	return (count);
}

bool	set_color(t_vars *v, char *line, char c)
{
	char	**rgb;
	int		color;

	if (count_commas(line) != 2)
		return (false);
	rgb = ft_split(line, ',');
	if (!rgb)
		return (false);
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3] || !is_color_value(rgb[0])
		|| !is_color_value(rgb[1]) || !is_color_value(rgb[2]))
		return (free_split(rgb), false);
	color = rgb_to_color(rgb);
	free_split(rgb);
	if (color == -1)
		return (false);
	if (c == 'c')
		v->ceiling_color = color;
	else if (c == 'f')
		v->floor_color = color;
	return (true);
}
