/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_helpers_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:43:40 by luozguo           #+#    #+#             */
/*   Updated: 2025/09/14 16:43:41 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/// @brief Convert unsigned long to hexadecimal string in reverse order to fill buf
/// @param u 
/// @param buf 
/// @param upper 
/// @return length of the string in buf
int utoa_hex_rev(unsigned long u, char *buf, int upper)
{
    int slen;
    char *hex;
    if (upper)
        hex = "0123456789ABCDEF";
    else 
        hex = "0123456789abcdef";
    slen = 0;
    while(u >= 16)
    {
        *buf = hex[u % 16]; // a more standard way to index into a lookup string
        buf ++;
        slen++;
        u /= 16;
    }
    *buf = hex[u % 16];
    slen++;

    return slen;
}

/// @brief Convert unsigned int to decimal string in reverse order
/// @param
/// @param buffer
/// @return length of the string in buffer

int	utoa_dec_rev(unsigned int u, char *buf)
{
	int	fil_len;

	fil_len = 0;
	while (u >= 10)
	{
		*buf = u % 10 + '0';
		buf++;
		fil_len++;
		u /= 10;
	}
	*buf = u % 10 + '0';
	fil_len++;
	return (fil_len);
}

/// @brief  Put filled buffer (in reverse order) to stdout
/// @param buf
/// @param len
/// @param err_flag
/// @return number of characters printed, or -1 on error and set *err_flag to -1
int put_buffer_rev(char *buf, int len, int *err_flag)
{
	int	count;
	
	if (len <= 0 || *err_flag)
		return (0);
	count = 0;
	while (len > 0)
	{
		count += write_wrapper(1, buf + len - 1, 1, err_flag);
		len--;
	}
	if (*err_flag)
		return (-1);
	return (count);
}

int put_num_cfg_left(t_numcfg n, int *err_flag)
{
	int count;
	if (*err_flag)
		return (0);
	count = 0;
	count += write_wrapper(1, n.prefix, n.prefix_len, err_flag);
	count += put_repeat('0', n.prec0, err_flag);
	count += put_buffer_rev(n.buf, n.fil_len, err_flag);
	count += put_repeat(' ', n.padding, err_flag);
	return (count);
}

/// @brief this is the only print function for all number specifiers(udxX).print number with configuration. print prefix, precision 0, buffer in reverse order, padding that decided by f.minus ,f.zero, precision./// @param n 
/// @param f 
/// @return number of characters printed
int put_num_cfg(t_numcfg n, t_fmt_parser f)
{
	int count;
	int err_flag;
	
	err_flag = 0;
	count = 0;
	if (f.minus)
		count += put_num_cfg_left(n, &err_flag);
	else if (f.zero && f.prec < 0)
	{
		count += write_wrapper(1, n.prefix, n.prefix_len, &err_flag);
		count += put_repeat('0', n.padding, &err_flag);
		count += put_repeat('0', n.prec0, &err_flag);
		count += put_buffer_rev(n.buf, n.fil_len, &err_flag);
	}
	else
	{
		count += put_repeat(' ', n.padding, &err_flag);
		count += write_wrapper(1, n.prefix, n.prefix_len, &err_flag);
		count += put_repeat('0', n.prec0, &err_flag);
		count += put_buffer_rev(n.buf, n.fil_len, &err_flag);
	}
	if (err_flag)
		return (-1);
	return (count);
}

