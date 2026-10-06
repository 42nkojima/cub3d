/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 20:00:33 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/06 20:00:33 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_error.h"
#include "cub_cleaner.h"
#include "libft.h"
#include <stdlib.h>

void	handle_error(t_vars *v, const char *msg, const char *detail)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putstr_fd((char *)msg, STDERR_FILENO);
	if (detail)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd((char *)detail, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	if (v)
		destroy_vars(v);
	exit(EXIT_FAILURE);
}
