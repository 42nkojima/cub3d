/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:56:05 by tmase             #+#    #+#             */
/*   Updated: 2025/05/09 17:35:20 by tmase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*sone;
	unsigned char	*stwo;

	sone = (unsigned char *)s1;
	stwo = (unsigned char *)s2;
	while (n--)
	{
		if (*sone != *stwo)
			return (*sone - *stwo);
		sone++;
		stwo++;
	}
	return (0);
}

// int main(void)
// {
// 	char *s1 = NULL;
// 	char *s2 = NULL;
// 	memcmp(s1, s2, 5);
// }
