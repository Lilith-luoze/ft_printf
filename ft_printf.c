#include "local_printf.h"
#include "public_printf.h"

int handle_format(const char **fmt_pp, va_list ap, t_fmt_parser *f_p);

int ft_printf(const char *fmt, ...)
{
    int count;
    va_list ap;
    t_fmt_parser f;

    va_start(ap,fmt);
    count = 0;
    while(*fmt)
    {
        if( *fmt != '%')
        {
            count += write(1, fmt, 1);
            fmt++;
            continue;
        }
        else
        {
            fmt++;
            count += handle_format(&fmt, ap, &f);
            if (*fmt == '\0')
                break;
            fmt++; //??
        }
    }
    va_end(ap);
    return count;
}

int handle_format(const char **fmt_pp, va_list ap, t_fmt_parser *f_p)
{
    *fmt_pp = parse_fmt_main(*fmt_pp, f_p); // renewed the fmt pointer
    parse_fmt_normalize(f_p);
    return (dispatch_parsed(ap , *f_p));
}

// # include <stdio.h>
// int main(void)
// {
//     int count = ft_printf("a%%b\n");
//     printf("Total characters printed: %d\n", count);
//     return 0;
// }

