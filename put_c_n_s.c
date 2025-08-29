#include "local_printf.h"

int	put_c(int c, t_fmt f)
{
	char	ch;

	ch = (char)c; // to make the intent clear
	return (write(1, &ch, 1));
}

/// @brief  Put string to stdout, return number of characters written
int	put_s_basic(char *s)
{
	int	count;

	count = 0;
	if (s == NULL)
		s = "(null)";
	while (*s)
	{
		write(1, s, 1);
		s++;
		count++;
	}
	return (count);
}

