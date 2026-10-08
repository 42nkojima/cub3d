/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_error.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 20:00:33 by nkojima           #+#    #+#             */
/*   Updated: 2026/10/06 20:00:33 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_ERROR_H
# define CUB_ERROR_H

# include "cub.h"

void	handle_error(t_vars *v, const char *msg, const char *detail);

#endif
