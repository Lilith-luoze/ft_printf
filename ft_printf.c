#include "ft_printf.h"

// specifiers
int ft_printf(const char *fmt, ...) // format string, ellipsis
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
        if (*fmt == '%') // skeleton of specifiers conversions
        {
            fmt++;
            if (*fmt == '\0') // guard a dangling '%'
                break;
            if(*fmt == 'c')
                count += put_c_basic(va_arg(ap, int)); // for var_functions, char promoted to int
            else if(*fmt == 'd' || *fmt == 'i')
                count += put_d_basic(va_arg(ap, int)); // fetch ap as int, then move it forward
            else if(*fmt == 's')
                count += put_s_basic(va_arg(ap, char *));
            else if (*fmt == 'p')
                count += put_p_basic(va_arg(ap, void *));
            else if(*fmt == 'u')
                count += put_u_basic(va_arg(ap, unsigned int));
            else if(*fmt == 'x' ||*fmt == 'X')
                count += put_h_basic(va_arg(ap, unsigned int), *fmt == 'X');
            else if(*fmt == '%')
                count += write(1, "%", 1);
            else //write as it is
            {
                count += write(1, "%", 1); // write the '%' character
                count += write(1, fmt, 1);     // write the unknown specifier
            }
            fmt++;
        }
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

