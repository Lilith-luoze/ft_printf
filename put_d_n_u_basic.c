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

/// @brief decide the prefix for %duxXp
/// @param negative 
/// @param f 
/// @param prefix_pp: pointer to pointer. modify the pointer to string
/// @return the length of prefix
int decide_prefix(int negative,t_fmt_parser f, char ** prefix_pp)
{
	if (f.hash && (f.spec == 'x' || f.spec == 'X'))
	{
		if (f.spec == 'x')
			*prefix_pp = "0x";
		else
			*prefix_pp = "0X";
		return (2);
	}
	if (negative)
		*prefix_pp = "-";
	else if (f.plus)
		*prefix_pp = "+";
	else if (f.space)
		*prefix_pp = " ";
	else
	{
		*prefix_pp = "";
		return (0);
	}
	return (1);
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

int put_num_cfg(t_numcfg n, t_fmt_parser f)
{
	int count;
	count = 0;
	if (f.minus)
	{
		count += write(1, n.prefix, n.prefix_len);
		count += put_repeat('0', n.prec0);
		count += put_buffer_rev(n.buf, n.fil_len);
		count += put_repeat(' ', n.padding);
	}
	else if (f.zero && f.prec < 0)
	{
		count += write(1, n.prefix, n.prefix_len);
		count += put_repeat('0', n.padding);
		count += put_repeat('0', n.prec0);
		count += put_buffer_rev(n.buf, n.fil_len);
	}
	else
	{
		count += put_repeat(' ', n.padding);
		count += write(1, n.prefix, n.prefix_len);
		count += put_repeat('0', n.prec0);
		count += put_buffer_rev(n.buf, n.fil_len);
	}
	return (count);
}

/// @brief Put decimal number to stdout, return number of characters written
// handles sign, precision (leading zeros), width, and flags (+, space, 0, -).
// prec never truncates digits
int	put_d(int d, t_fmt_parser f)
{
	t_numcfg n;

	n.negative = itoul(d, &n.un);
	n.fil_len = utoa_dec_rev(n.un, n.buf);
	n.prec0 = num_prec0(f, &n.fil_len, n.un);
	n.prefix_len = decide_prefix(n.negative, f, &(n.prefix));
	n.padding = f.width - (n.prefix_len + n.prec0 + n.fil_len);
	if (n.padding < 0)
		n.padding = 0;

	return (put_num_cfg(n, f));
}

int put_u(unsigned int u, t_fmt_parser f)
{
	t_numcfg n;

	n.negative = 0;
	n.prefix_len = 0;
	n.un = (unsigned long)u;
	n.fil_len = utoa_dec_rev(n.un, n.buf);
	n.prec0 = num_prec0(f, &n.fil_len, n.un);
	n.padding = f.width - (n.prefix_len + n.prec0 + n.fil_len);
	if (n.padding < 0)
		n.padding = 0;

	return (put_num_cfg(n, f));
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


// prefix is with new things - 0x or 0X
int put_hex(unsigned int h, t_fmt_parser f, int upper)
{
    t_numcfg n;
    
	n.negative = 0;
	n.prefix_len = decide_prefix(n.negative, f, &n.prefix);
	n.un = (unsigned long)h;
	n.fil_len = utoa_hex_rev(n.un, n.buf, upper);
	n.prec0 = num_prec0(f, &n.fil_len, n.un);
	n.padding = f.width - (n.prefix_len + n.prec0 + n.fil_len);
	if (n.padding < 0)
		n.padding = 0;

	return (put_num_cfg(n, f));
}

int put_ptr(void *p, t_fmt_parser f)
{
    t_numcfg n;
    
	n.negative = 0;
	n.prefix_len = 2;
	n.prefix = "0x";
	n.un = (unsigned long)p;
	n.fil_len = utoa_hex_rev(n.un, n.buf, 0);
	n.prec0 = num_prec0(f, &n.fil_len, n.un);
	n.padding = f.width - (n.prefix_len + n.prec0 + n.fil_len);
	if (n.padding < 0)
		n.padding = 0;

	return (put_num_cfg(n, f));
}


