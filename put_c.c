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
		*err = 1;
		return -1;
	}
	return ret;
}

// width is the only flag that matters here
// if minus → left-justified: char first, then spaces
// else → spaces first, then char
int	put_c(int c, t_fmt_parser f)
{
	char	ch;
	int		count;
	int err_flag;
	
	err_flag = 0;
	ch = (char)c;
	count = 0;

	if (f.minus)
	{
		count += write_wrapper(1, &ch, 1, &err_flag);
		count += put_repeat_wrapper(' ', f.width - 1, &err_flag);
	}
	else
	{
		count += put_repeat_wrapper(' ', f.width - 1, &err_flag);
		count += write_wrapper(1, &ch, 1, &err_flag);
	}
	if (err_flag)
		return -1;
	return (count);
}


