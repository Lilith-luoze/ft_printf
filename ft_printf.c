#include "ft_printf.h"

/// @brief  Prints formatted output to stdout.
/// @details This function takes a format string and variable arguments,
/// @param fmt  The format string that specifies how to format the output.
/// @param ...  Variable arguments that match the format specifiers in fmt.
/// @return  The number of characters printed to stdout.



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
        else if (*(fmt + 1) == '%') 
        {
            count += write(1, "%", 1);
            fmt = fmt + 2 ;
        }
        else 
        {
            // Handle other format specifiers in future steps
            fmt++;
        }
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

