/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:56:44 by tmase             #+#    #+#             */
/*   Updated: 2025/05/14 16:14:11 by tmase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	j;
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = dest_len;
	j = 0;
	if (destsize == 0 || destsize <= dest_len)
		return (src_len + destsize);
	while (src[j] && i < destsize - 1)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest_len + src_len);
}

// int main(void)
// {
// 	char dest[20] = "Hello";
// 	char src[] = " World!";
// 	size_t destsize = sizeof(dest);

// 	printf("Before strlcat: %s\n", dest);
// 	size_t result = ft_strlcat(dest, src,11);
// 	printf("After strlcat: %s\n", dest);
// 	printf("Total length: %zu\n", result);

// 	return 0;
// }
