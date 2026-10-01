/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:57:12 by tmase             #+#    #+#             */
/*   Updated: 2025/05/07 20:55:59 by tmase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if ('A' <= c && c <= 'Z')
		return (c + 32);
	return (c);
}

// int main(void)
// {
// 	printf("%c\n", (char)ft_tolower('A' - 1));
// 	printf("%c\n", (char)ft_tolower('A'));
// 	printf("%c\n", (char)ft_tolower('Z' + 1));
// 	printf("%c\n", (char)ft_tolower('Z'));
// }
