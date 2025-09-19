#include "ft_printf.h"



// width is the only flag that matters here
// if minus → left-justified: char first, then spaces
// else → spaces first, then char
int	put_c(int c, t_fmt_parser f)
{
	char	ch;
	int		count;
	int		err_flag;

	err_flag = 0;
	ch = (char)c;
	count = 0;

	if (f.minus)
	{
		count += write_wrapper(1, &ch, 1, &err_flag);
		count += put_repeat(' ', f.width - 1, &err_flag);
	}
	else
	{
		count += put_repeat(' ', f.width - 1, &err_flag);
		count += write_wrapper(1, &ch, 1, &err_flag);
	}
	if (err_flag)
		return -1;
	return (count);
}


