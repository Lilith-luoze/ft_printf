#include "ft_printf.h"


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
