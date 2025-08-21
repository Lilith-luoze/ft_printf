#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h> // for variable argument lists (va_list, va_start, va_end)
# include <unistd.h> // for write()
#include "ft_libft.h" // for my libc

typedef struct s_fmt {
    int left;    // '-' flag (0/1) — ignore for now
    int zero;    // '0' flag (0/1) — ignore for now
    int plus;    // '+' flag (0/1) — ignore for now
    int space;   // ' ' flag (0/1) — ignore for now
    int hash;   // '#' flag (0/1) — ignore for now
    int width;   // -1 if not set
    int prec;    // -1 if not set
    char spec;   // c s p d i u x X %
} t_fmt;

static void fmt_init(t_fmt *f) {
    f->left=f->zero=f->plus=f->space=f->hash=0;
    f->width = -1; f->prec = -1; f->spec = 0;
}

# if defined(__linux__)
#  define NULL_PTR "(nil)"
# elif defined(__APPLE__)
#  define NULL_PTR "0x0"
# endif

int ft_printf(const char *fmt, ...);
int ft_putchar(int c);
int ft_putstr(char *s);
int ft_putnbr(int n);
int ft_putunsigned(unsigned int n);
int ft_puthex(unsigned int n, int uppercase);
int ft_putptr(void *p);

#endif
