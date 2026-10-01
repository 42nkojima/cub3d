/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:56:29 by tmase             #+#    #+#             */
/*   Updated: 2025/05/14 15:27:43 by tmase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	*get_word(const char *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	*free_sprit(char **split, int j)
{
	while (j >= 0)
	{
		free(split[j]);
		j--;
	}
	free(split);
	return (NULL);
}

static char	**helper(const char *s, char c, char **split)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			split[j] = get_word(&s[i], c);
			if (!split[j])
				return (free_sprit(split, j - 1));
			j++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	split[j] = NULL;
	return (split);
}

char	**ft_split(const char *s, char c)
{
	char	**split;
	int		count;

	if (!s)
		return (NULL);
	count = count_word(s, c);
	split = malloc(sizeof(char *) * (count + 1));
	if (!split)
		return (NULL);
	split = helper(s, c, split);
	return (split);
}

// int main(void)
// {
// 	char **result = ft_split("Hello ,,,, ,,World! ,This is a test.", ',');
// 	for (int i = 0; result[i] != NULL; i++)
// 	{
// 		printf("%s\n", result[i]);
// 		free(result[i]);
// 	}
// 	free(result);
// 	return 0;
// }
