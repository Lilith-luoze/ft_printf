#include "ft_printf.h"


int	put_percent(t_fmt_parser f)
{
	int	count;

	count = 0;
	if (f.minus)
	{
		count += write(1, "%", 1);
		count += put_repeat(' ', f.width - 1);
	}
	else
	{
		if (f.zero)
			count += put_repeat('0', f.width - 1);
		else
			count += put_repeat(' ', f.width - 1);
		count += write(1, "%", 1);
	}
	return (count);
}
