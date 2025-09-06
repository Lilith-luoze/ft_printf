#include "ft_printf.h"

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
        fmt++;
        if (*fmt == '\0')
            break;
        parser_init(&f);
        fmt = parse_fmt_main(fmt, &f); // parse fmt and move fmt pointer
        parse_fmt_normalize(&f);
        count += dispatch_parsed(ap, f);
    }
    va_end(ap);
    return count;
}
