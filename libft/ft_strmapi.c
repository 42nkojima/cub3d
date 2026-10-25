/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:14:00 by nkojima           #+#    #+#             */
/*   Updated: 2025/05/30 19:38:57 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Applies a function to each character of a string to create a new string.
 *
 * Params:
 * @s: The string to iterate over.
 * @f: The function to apply to each character (index, char) -> char.
 *
 * Return:
 * A new string with the results of function f applied to each character,
 * or NULL if allocation fails or if s or f is NULL.
 */
char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;
	size_t			len;

	len = ft_strlen(str);
	result = malloc(sizeof(*result) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = f(i, str[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

// #include <stdio.h>
// #include <string.h>

// static char	to_upper(unsigned int i, char c)
// {
// 	(void)i;
// 	if (c >= 'a' && c <= 'z')
// 		return (c - 32);
// 	return (c);
// }

// int	main(void)
// {
// 	char	*str1;
// 	char	*result;

// 	// Test 1: a normal string to uppercase
// 	str1 = "hello world";
// 	printf("Test 1: uppercase\n");
// 	printf("original: %s\n", str1);
// 	result = ft_strmapi(str1, to_upper);
// 	printf("result: %s\n", result);
// 	printf("expected: HELLO WORLD\n");
// 	printf("status: %s\n\n", strcmp(result, "HELLO WORLD") == 0 ? "OK" : "KO");
// 	free(result);
// 	// Test 2: empty string
// 	printf("Test 2: empty string\n");
// 	result = ft_strmapi("", to_upper);
// 	printf("result: \"%s\"\n", result);
// 	printf("expected: \"\"\n");
// 	printf("status: %s\n", strcmp(result, "") == 0 ? "OK" : "KO");
// 	free(result);
// 	return (0);
// }
