#include "local_printf.h"

// avoid len<= 0. clever trick -- chunking method. 
int put_repeat(char r , int len)
{
	int count;
	char str[64];
	if(len <= 0)
		return(0);
	count = 0;
	while (count < 64)
		str[count++] = r;
	count = 0;
	while(len)
	{
		if (len <= 64)
		{
			count += write(1, str, len);
			return count;
		}
		else
		{
			write(1, str, 64);
			count += 64;
			len -= 64;
		}
	}
	return count;
}

// width is the only flag that matters here
// if minus → left-justified: char first, then spaces
// else → spaces first, then char
int	put_c(int c, t_fmt f)
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

// put s with eff_len
int put_s_trunc(const char *str , int eff_len)
{
	return write(1, str, eff_len);
}

/// @brief  Put string to stdout, return number of characters written
int	put_s(char *s , t_fmt f)
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
	if (f.prec >= 0 && f.prec <= (int)str_len)
		eff_len = f.prec;
	else
		eff_len = str_len;
	//minus and width
	if (f.minus)
	{
		count += put_s_trunc(str, eff_len);
		count += put_repeat(' ', f.width - eff_len);
	}
	else
	{
		count += put_repeat(' ', f.width - eff_len);
		count += put_s_trunc(str, eff_len);
	}
	return (count);
}

