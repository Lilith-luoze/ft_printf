#ifndef LOCAL_PRINTF_H
# define LOCAL_PRINTF_H

# include <stdarg.h> // for variable argument lists (va_list, va_start, va_end)
# include <unistd.h> // for write()
# include "libft/libft.h" // for my libc (check)

typedef struct s_fmt {
    int minus;    // '-' flag (0/1)
    int zero;    // '0' flag (0/1)
    
    int width;   // -1 if not set
    int prec;    // -1 if not set

    char spec;   // c s p d i u x X %


    int space;   // ' ' flag (0/1) - ignore for now
    int hash;   // '#' flag (0/1) — ignore for now
    int plus;    // '+' flag (0/1)
} t_fmt;


# if defined(__linux__)
# define NULL_PTR "(nil)"
# elif defined(__APPLE__)
# define NULL_PTR "0x0"
# endif

int	utoa_dec_rev(unsigned int u, char *buffer);
int	put_buffer_rev(char *buffer, int len);

int utoa_hex_rev(unsigned long u, char *buffer, int upper);

int put_c(int c, t_fmt f);
int put_s(char *s, t_fmt f);
int put_d(int d, t_fmt f);
int put_u(unsigned int u, t_fmt f);
int put_hex(unsigned int u, t_fmt f, int upper);
int put_p(void *p, t_fmt f);
int put_percent(t_fmt f);



#endif
