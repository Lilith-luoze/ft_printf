#include "ft_printf.h"

/// @brief  Put string to stdout, return number of characters written
int	put_s(char *s , t_fmt_parser f)
{
	int	count;
	const char *str;
	size_t str_len;
	if (!s)
		return (write(1, &NULL_PTR,sizeof(NULL_PTR) - 1));
	str = (const char *) s;
	count = 0;
	str_len = ft_strlen(str);

	//prec
	int eff_len;
	if (f.prec >= 0 && f.prec < (int)str_len)
		eff_len = f.prec;
	else
		eff_len =  (int)str_len;
	//minus and width
	if (f.minus)
	{
		count += write(1, str, eff_len);
		count += put_repeat(' ', f.width - eff_len);
	}
	else
	{
		count += put_repeat(' ', f.width - eff_len);
		count += write(1, str, eff_len);
	}
	return (count);
}
