#include "ft_printf.h"

/// @brief  Prints formatted output to stdout.
/// @details This function takes a format string and variable arguments,
/// @param fmt  The format string that specifies how to format the output.
/// @param ...  Variable arguments that match the format specifiers in fmt.
/// @return  The number of characters printed to stdout.

/* Step 1 — MVP: loop + handle %% only
 *
 * 1. Define ft_printf(const char *fmt, ...). chekc
 * 2. Setup va_list with va_start / va_end (even if unused yet). check 
 * 3. Loop through each char in fmt: 
 *      - If not '%': write it with write(1, &c, 1), count++.
 *      - If '%' followed by '%': write one '%', advance fmt by 2, count++.
 *      - If '%' followed by something else: leave it for later steps.
 * 4. Return total count of characters written.
 *
 * Test:
 *   ft_printf("a%%b") → prints "a%b", returns 3.
 */

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

