/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:09:13 by luozguo           #+#    #+#             */
/*   Updated: 2025/08/26 18:24:32 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Calculates the length of the string of an integer.
/// @param nbr 
/// @return 
static size_t	ft_itoa_len(int nbr)
{
	size_t	len;

	len = 0;
	if (nbr == 0)
		len++;
	if (nbr < 0)
		len++;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

/// @brief Converts an integer to a string buffer that you can free.
/// @param n 
/// @return 

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	size_t	i;

	i = 0;
	str = NULL;
	len = ft_itoa_len(n);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		if (n < 0)
			str[len - 1 - i] = '0' - n % 10;
		else
			str[len - 1 - i] = '0' + n % 10;
		i++;
		n = n / 10;
	}
	return (str);
}
