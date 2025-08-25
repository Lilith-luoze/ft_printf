#include "ft_printf.h"

/// @brief  Prints formatted output to stdout.
/// @details This function takes a format string and variable arguments,
/// @param fmt  The format string that specifies how to format the output.
/// @param ...  Variable arguments that match the format specifiers in fmt.
/// @return  The number of characters printed to stdout.

// specifier
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
        }
        else if (*fmt == '%') // skeleton of specifiers conversions
        {
            fmt++;
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
                count += put_h_basic(va_arg(ap, unsigned int));
            else if(*fmt == '%')
                count += write(1, "%", 1);
            else // 
                //should be smth
            fmt++;
    }
    va_end(ap);
    return count;
}

# include <stdio.h>
int main(void)
{
    int count = ft_printf("a%%b\n");
    printf("Total characters printed: %d\n", count);
    return 0;
}

