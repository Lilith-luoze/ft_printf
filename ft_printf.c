#include "ft_printf.h"

/// @brief  Prints formatted output to stdout.
/// @details This function takes a format string and variable arguments,
/// @param fmt  The format string that specifies how to format the output.
/// @param ...  Variable arguments that match the format specifiers in fmt.
/// @return  The number of characters printed to stdout.

/* Step 1 — MVP: loop + handle %% only
 *
 * 1. Define ft_printf(const char *fmt, ...).
 * 2. Setup va_list with va_start / va_end (even if unused yet).
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

    while(*fmt)
    {
        write(1, fmt,1);
        fmt++;
        count++;
    }
    return count;
}