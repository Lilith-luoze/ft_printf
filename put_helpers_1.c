#include "ft_printf.h"

/// @brief write. check err_flag before write, and set err_flag if error occurs
/// @param fd 
/// @param buf 
/// @param len 
/// @param err 
/// @return printed length, or -1 on error and set *err_flag to 1.
int write_wrapper(int fd, const void *buf, size_t len , int *err_flag)
{
	int ret;

	if (*err_flag)
		return -1;
	ret = write(fd, buf, len);
	if (ret == -1)
	{
		*err_flag = 1;
		return -1;
	}
	return ret;
}

// avoid len<= 0. clever trick -- chunking method. 
int put_repeat(char r , int len, int *err_flag)
{
	int count;
	char str[64];

	if(len <= 0 || *err_flag)
		return(0);
	count = 0;
	while (count < 64)
		str[count++] = r;
	count = 0;
	while(len)
	{
		if (len <= 64)
		{
			count += write_wrapper(1, str, len, err_flag);
			return count;
		}
		else
		{
			count += write_wrapper(1, str, 64, err_flag);
			len -= 64;
		}
	}
	if (*err_flag)
		return -1;
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

int put_buffer_rev(char *buf, int len, int *err_flag)
{
	int	count;

	if (len <= 0 || *err_flag)
		return (0);
	count = 0;
	while (len > 0)
	{
		write_wrapper(1, buf + len - 1, 1, err_flag);
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
