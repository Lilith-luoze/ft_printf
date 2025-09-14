/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_helpers_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:43:37 by luozguo           #+#    #+#             */
/*   Updated: 2025/09/14 16:43:38 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/// @brief write. check err_flag before write, and set err_flag if error occurs
/// @param fd 
/// @param buf 
/// @param len 
/// @param err 
/// @return printed length, or -1 on error and set *err_flag to 1.
int write_wrapper(int fd, const void *buf, size_t len , int *err_flag)
{
	int ret;

	if (*err_flag)
		return -1;
	ret = write(fd, buf, len);
	if (ret == -1)
	{
		*err_flag = 1;
		return -1;
	}
	return ret;
}


/// @brief  Convert int to unsigned long, and set negative flag
/// @param n 
/// @param un being set to absolute value of n
/// @return negative flag, 1 if n < 0
int itoul(int n, unsigned long *un)
{
	if (n < 0)
	{
		*un = (unsigned long)(-(long)n);
		return (1);
	}
	else
	{
		*un = (unsigned long)n;
		return (0);
	}
}

int num_prec0(t_fmt_parser f, int *fil_len , unsigned long un)
{
	int prec0;
	
	if (f.prec > *fil_len)
		prec0 = f.prec - *fil_len;
	else if (f.prec == 0 && un == 0)
	{
		*fil_len = 0;
		prec0 = 0;
	}
	else
		prec0 = 0;
	return (prec0);
}

// avoid len<= 0. clever trick -- chunking method. 
int put_repeat(char r , int len, int *err_flag)
{
	int count;
	char str[64];

	if(len <= 0 || *err_flag)
		return(0);
	count = 0;
	while (count < 64)
		str[count++] = r;
	count = 0;
	while(len)
	{
		if (len <= 64)
		{
			count += write_wrapper(1, str, len, err_flag);
			return count;
		}
		else
		{
			count += write_wrapper(1, str, 64, err_flag);
			len -= 64;
		}
	}
	if (*err_flag)
		return -1;
	return count;
}


/// @brief decide the prefix for %duxXp
/// @param negative 
/// @param f 
/// @param prefix_pp: pointer to pointer. modify the pointer to string
/// @return the length of prefix
int decide_prefix_for_dx(int negative,t_fmt_parser f, char ** prefix_pp)
{
	if (f.hash && (f.spec == 'x' || f.spec == 'X'))
	{
		if (f.spec == 'x')
			*prefix_pp = "0x";
		else
			*prefix_pp = "0X";
		return (2);
	}
	if (negative)
		*prefix_pp = "-";
	else if (f.plus)
		*prefix_pp = "+";
	else if (f.space)
		*prefix_pp = " ";
	else
	{
		*prefix_pp = "";
		return (0);
	}
	return (1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}