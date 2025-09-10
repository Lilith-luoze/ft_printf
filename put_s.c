#include "ft_printf.h"

int put_s_effctive_length(char *s, t_fmt_parser f)
{

	int eff_len;
	int str_len = 0;
	str_len = (int)ft_strlen((const char *)s);
	if (f.prec >= 0 && f.prec < str_len)
		eff_len = f.prec;
	else
		eff_len =  str_len;
	return (eff_len);
}

/// @brief  Put string to stdout, return number of characters written
int	put_s(char *s , t_fmt_parser f)
{
	int	count;
	int eff_len;
	int err_flag;

	if (s == NULL)
		s = "(null)";
	count = 0;
	err_flag = 0;

	//create a function that deal with prec and str_len, obtain the effective length
	eff_len = put_s_effctive_length(s, f);
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
