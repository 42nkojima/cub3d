/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:55:20 by tmase             #+#    #+#             */
/*   Updated: 2025/08/01 19:11:12 by tmase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str == '0')
		str++;
	if (*str < '1' || *str > '9')
		return (0);
	while (*str)
	{
		result = (result * 10) + ((*str - '0') * sign);
		str++;
		if (*str < '0' || *str > '9')
			break ;
	}
	return (result);
}

// int main(void)
// {
// 	char str[] = "1   -23";
// 	int result = ft_atoi(str);
// 	printf("The converted number is %d\n", result);
// 	return 0;
// }
