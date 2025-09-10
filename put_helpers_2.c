#include "ft_printf.h"

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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

