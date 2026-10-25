/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 14:02:49 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/25 14:02:49 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

bool	set_texture(t_vars *v, t_dir dir, char *path)
{
	v->tex_path[dir] = ft_strdup(path);
	return (v->tex_path[dir] != NULL);
}
