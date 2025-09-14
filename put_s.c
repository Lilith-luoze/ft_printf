/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_s.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:43:49 by luozguo           #+#    #+#             */
/*   Updated: 2025/09/14 16:43:50 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int put_s_effctive_length_and_null_check(char **s, t_fmt_parser *f)
{

	int eff_len;
	int str_len = 0;
	
	if (*s == NULL )
	{
		*s = "(null)";
		if (f->prec >= 0 && f->prec < 6)
			f->prec = 0;
	}
	str_len = (int)ft_strlen((const char *)(*s));
	if (f->prec >= 0 && f->prec < str_len)
		eff_len = f->prec;
	else
		eff_len =  str_len;
	return (eff_len);
}

/// @brief  Put string to stdout, return number of characters written
/// @param s
/// @param f
/// @return number of characters printed, or -1 on error
int	put_s(char *s , t_fmt_parser f)
{
	int	count;
	int eff_len;
	int err_flag;

	count = 0;
	err_flag = 0;

	//create a function that deal with prec and str_len, obtain the effective length
	eff_len = put_s_effctive_length_and_null_check(&s, &f);
	//minus and width
	if (f.minus)
	{
		count += write_wrapper(1, s, eff_len, &err_flag);
		count += put_repeat(' ', f.width - eff_len, &err_flag);
	}
	else
	{
		count += put_repeat(' ', f.width - eff_len, &err_flag);
		count += write_wrapper(1, s, eff_len, &err_flag);
	}
	if (err_flag)
		return -1;
	return (count);
}
