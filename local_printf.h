#ifndef LOCAL_PRINTF_H
# define LOCAL_PRINTF_H

# include <stdarg.h> // for variable argument lists (va_list, va_start, va_end)
# include <unistd.h> // for write()
# include "ft_libft.h" // for my libc (check)

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

int	put_c_basic(int c);

int	put_s_basic(char *s);

int	utoa_dec_rev(unsigned int u, char *buffer);
int	put_buffer_rev(char *buffer, int len);
int	put_d_basic(int d);
int put_u_basic(unsigned int u);

int utoa_hex_rev(unsigned long u, char *buffer, int upper);
int put_p_basic(void *p);
int put_hex_basic(unsigned int h, int upper);




#endif
