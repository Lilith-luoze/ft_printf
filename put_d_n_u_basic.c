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
int decide_prefix_int(int negative,t_fmt f, char * prefix)
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

/// @brief Put decimal number to stdout, return number of characters written
// handles sign, precision (leading zeros), width, and flags (+, space, 0, -).
// prec never truncates digits
int	put_d(int d, t_fmt f)
{
	long n;
	unsigned long un;
	int negative;

	n = (long)d;       // widen to avoid INT_MIN issues
	negative = 0;
	if (n < 0)
	{
		negative = 1;
		un = (unsigned long)(-n);
	}
	else
		un = (unsigned long)n;

	char buf[32];
	int fil_len;

	fil_len = utoa_dec_rev(un, buf);

	int zeros;
	if (f.prec > fil_len)
		zeros = f.prec - fil_len;
	else if (f.prec == 0 && un == 0)
		fil_len = 0;   // special rule: ".0" with 0 → print nothing
	else
		zeros = 0;

	// prefix
	
	int prefix_len;
	char prefix;
	prefix_len = decide_prefix_int(negative, f, &prefix);

	
	int total_core;   // prefix + zeros + digits
	int padding;

	total_core = prefix_len + zeros + fil_len;
	padding = f.width - total_core;
	if (padding < 0)
		padding = 0;

	int count = 0;
	if (f.minus)
	{
		count += write(1, prefix, prefix_len);
		count += put_repeat('0', zeros);
		count += put_buffer_rev(buf, fil_len);
		count += put_repeat(' ', padding);

	}
	else if (f.zero && f.prec < 0 && !f.minus)
	{
		count += write(1, prefix, prefix_len);
		count += put_repeat('0', padding);
		count += put_repeat('0', zeros);
		count += put_buffer_rev(buf, fil_len);
	}
	else
	{
		count += put_repeat(' ', padding);
		count += write(1, prefix, prefix_len);
		count += put_repeat('0', zeros);
		count += put_buffer_rev(buf, fil_len);
	}
}

int put_u_basic(unsigned int u)
{
	int slen;        // string length in buffer
	char buffer[10]; // max 10 digits for 32-bit int

	slen = utoa_dec_rev(u, buffer);
	return (put_buffer_rev(buffer, slen));
}