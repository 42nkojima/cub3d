/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:10:54 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 20:13:16 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Excerpts a substring from the string `s`.
 *
 * Params:
 * @s: The source string.
 * @start: The starting index of the substring.
 * @len: The maximum length of the substring.
 *
 * Return:
 * A newly allocated substring, or NULL on failure.
 */
char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	str_len;
	size_t	substr_len;

	str_len = ft_strlen(str);
	if ((size_t)start >= str_len)
		return (ft_calloc(1, 1));
	substr_len = str_len - (size_t)start;
	if (substr_len > len)
		substr_len = len;
	substr = malloc(sizeof(*substr) * (substr_len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < substr_len && str[start + i])
	{
		substr[i] = str[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*result;

// 	// Test case 1: normal substring
// 	result = ft_substr("Hello, world!", 7, 5);
// 	printf("Test 1: %s\n", result); // expected: "world"
// 	free(result);
// 	// Test case 2: start is past the end
// 	result = ft_substr("Hello, world!", 20, 5);
// 	printf("Test 2: %s\n", result); // expected: ""
// 	free(result);
// 	// Test case 3: len is longer than the rest
// 	result = ft_substr("Hello, world!", 7, 50);
// 	printf("Test 3: %s\n", result); // expected: "world!"
// 	free(result);
// 	// Test case 4: substring of an empty string
// 	result = ft_substr("", 0, 5);
// 	printf("Test 4: %s\n", result); // expected: ""
// 	free(result);
// 	// Test case 5: len is 0
// 	result = ft_substr("Hello, world!", 7, 0);
// 	printf("Test 5: %s\n", result); // expected: ""
// 	free(result);
// 	// Test case 6: pass a NULL pointer
// 	result = ft_substr(NULL, 0, 5);
// 	printf("Test 6: %s\n", result); // expected: undefined behavior (as in libc)
// 	free(result);
// 	return (0);
// }
