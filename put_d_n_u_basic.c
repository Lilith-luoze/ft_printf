# include "local_printf.h"

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

/// @brief  Put buffer in reverse order to stdout, return number of characters written 

int put_buffer_rev(char *buf, int len)
{
	int	count;

	count = 0;
	while (len > 0)
	{
		write(1, buf + len - 1, 1);
		len--;
		count++;
	}
	return (count);
}
int decide_prefix_num(int negative,t_fmt f, char * prefix)
{
	if (negative)
		*prefix = '-';
	else if (f.plus)
		*prefix = '+';
	else if (f.space)
		*prefix = ' ';
	else
		*prefix = '\0';
	return (*prefix != '\0');
}

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
int num_prec0(t_fmt f, int *fil_len , unsigned long un)
{
	int prec0s;

	if (f.prec > *fil_len)
		prec0s = f.prec - *fil_len;
	else if (f.prec == 0 && un == 0)
	{
		*fil_len = 0;
		prec0s = 0;
	}
	else
		prec0s = 0;
	return (prec0s);
}

int put_num_inctx(t_numctx n, t_fmt f)
{
	int count;
	count = 0;
	if (f.minus)
	{
		count += write(1, n.prefix, n.has_prefix);
		count += put_repeat('0', n.prec0);
		count += put_buffer_rev(n.buf, n.fil_len);
		count += put_repeat(' ', n.padding);
	}
	else if (f.zero && f.prec < 0)
	{
		count += write(1, n.prefix, n.has_prefix);
		count += put_repeat('0', n.padding);
		count += put_repeat('0', n.prec0);
		count += put_buffer_rev(n.buf, n.fil_len);
	}
	else
	{
		count += put_repeat(' ', n.padding);
		count += write(1, n.prefix, n.has_prefix);
		count += put_repeat('0', n.prec0);
		count += put_buffer_rev(n.buf, n.fil_len);
	}
	return (count);
}

/// @brief Put decimal number to stdout, return number of characters written
// handles sign, precision (leading zeros), width, and flags (+, space, 0, -).
// prec never truncates digits
int	put_d(int d, t_fmt f)
{
	t_numctx n;

	n.negative = itoul(d, &n.un);
	n.fil_len = utoa_dec_rev(n.un, n.buf);
	n.prec0 = num_prec0(f, &n.fil_len, n.un);
	n.has_prefix = decide_prefix_num(n.negative, f, &n.prefix);
	n.padding = f.width - (n.has_prefix + n.prec0 + n.fil_len);
	if (n.padding < 0)
		n.padding = 0;

	return (put_num_inctx(n, f));
}

int put_u(unsigned int u, t_fmt f)
{
	t_numctx n;

	n.negative = 0;
	n.un = (unsigned long)u;
	n.fil_len = utoa_dec_rev(n.un, n.buf);
	n.prec0 = num_prec0(f, &n.fil_len, n.un);
	n.has_prefix = decide_prefix_num(n.negative, f, &n.prefix);
	n.padding = f.width - (n.has_prefix + n.prec0 + n.fil_len);
	if (n.padding < 0)
		n.padding = 0;

	return (put_num_inctx(n, f));
}

