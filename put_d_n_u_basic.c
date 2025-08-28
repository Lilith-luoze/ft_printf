# include "local_printf.h"

/// @brief Convert unsigned int to decimal string in reverse order
/// @param
/// @param buffer
/// @return length of the string in buffer

int	utoa_dec_rev(unsigned int u, char *buffer)
{
	int	i;

	i = 0;
	while (u >= 10)
	{
		*buffer = u % 10 + '0';
		buffer++;
		i++;
		u /= 10;
	}
	*buffer = u % 10 + '0';
	i++;
	return (i);
}

/// @brief  Put buffer in reverse order to stdout, return number of characters written 

int put_buffer_rev(char *buffer, int len)
{
	int	count;

	count = 0;
	while (len > 0)
	{
		write(1, buffer + len - 1, 1);
		len--;
		count++;
	}
	return (count);
}

/// @brief Put decimal number to stdout, return number of characters written

int	put_d_basic(int d)
{
	long	l;

	int slen;        // string length in buffer
	char buffer[10]; // max 10 digits for 32-bit int
	l = (long)d;
	slen = 0;
	if (d < 0)
	{
		write(1, "-", 1);
		slen = utoa_dec_rev((unsigned int)(-l), buffer);
		return (put_buffer_rev(buffer, slen) + 1);
	}
	else
	{
		slen = utoa_dec_rev((unsigned int)l, buffer);
		return (put_buffer_rev(buffer, slen));
	}
}

int put_u_basic(unsigned int u)
{
	int slen;        // string length in buffer
	char buffer[10]; // max 10 digits for 32-bit int

	slen = utoa_dec_rev(u, buffer);
	return (put_buffer_rev(buffer, slen));
}