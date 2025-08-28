#include "local_printf.h"
#include "public_printf.h"

int dispatch_spec(const char *fmt , va_list ap)
{
    if(*fmt == 'c')
        return put_c_basic(va_arg(ap, int)); // for var_functions, char promoted to int
    else if(*fmt == 's')
        return put_s_basic(va_arg(ap, char *));
    else if(*fmt == 'd' || *fmt == 'i')
        return put_d_basic(va_arg(ap, int)); // fetch ap as int, then move it forward
    else if(*fmt == 'x' ||*fmt == 'X')
        return put_hex_basic(va_arg(ap, unsigned int), *fmt == 'X');
    else if (*fmt == 'p')
        return put_p_basic(va_arg(ap, void *));
    else if(*fmt == 'u')
        return put_u_basic(va_arg(ap, unsigned int));
    else if(*fmt == '%')
        return write(1, "%", 1);
    else //write as it is
    {
        write(1, "%", 1); // write the '%' character
        return (1 + write(1, fmt, 1));     // write the unknown specifier
    }
}

int ft_printf(const char *fmt, ...)
{
    int count = 0;
    va_list ap;
    va_start(ap,fmt);

    while(*fmt)
    {
        if( *fmt != '%')
        {
            count += write(1, fmt, 1);
            fmt++;
            continue;
        }
        // skeleton of specifiers conversions
        
        fmt++;
        if (*fmt == '\0') // guard a dangling '%'
            break;
        count += dispatch_spec(fmt , ap);
        fmt++;
    }
    va_end(ap);
    return count;
}

// # include <stdio.h>
// int main(void)
// {
//     int count = ft_printf("a%%b\n");
//     printf("Total characters printed: %d\n", count);
//     return 0;
// }

