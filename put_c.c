#include "ft_printf.h"

// width is the only flag that matters here
// if minus → left-justified: char first, then spaces
// else → spaces first, then char
int	put_c(int c, t_fmt_parser f)
{
	char	ch;
	int		count;

	ch = (char)c;
	count = 0;

	if (f.minus)
	{
		count += write(1, &ch, 1);
		count += put_repeat(' ', f.width - 1);
	}
	else
	{
		count += put_repeat(' ', f.width - 1);
		count += write(1, &ch, 1);
	}
	return (count);
}


