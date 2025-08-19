#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h> // for variable argument lists (va_list, va_start, va_end)
# include <unistd.h> // for write()

int ft_printf(const char *fmt, ...);
int ft_putchar(int c);
int ft_putstr(char *s);
int ft_putnbr(int n);
int ft_putunsigned(unsigned int n);
int ft_puthex(unsigned int n, int uppercase);
int ft_putptr(void *p);

#endif
