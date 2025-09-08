#include "ft_printf.h"

// call write, at success increment count, at failure return -1
int write_wrapper_in_printf(int fd, const void *buf, size_t len , int *count)
{
    int ret;
    
    ret = write(fd, buf, len);
    if (ret == -1)
        return -1;
    *count += ret;
    return ret;
}

/// @brief advance fmt pointer by 1, if it reaches null, return 1
/// @param fmt 
/// @return 
int advance_fmt_isnul(const char **fmt)
{
    *fmt += 1;
    if (**fmt == '\0')
        return 1;
    return 0;
}

/// @brief process one conversion specifier
/// @param ap 
/// @param fmt 
/// @param f 
/// @return number of printed characters, or -1 on error
int handle_conversion(va_list ap, const char **fmt, t_fmt_parser *f)
{
    parser_init(f);
    *fmt = parse_fmt(*fmt, f); // parse fmt and move fmt pointer
    parse_fmt_normalize(f);
    return dispatch_parsed(ap, *f);
}

/*to do:
- write func to check for wrong return (check all the way to each branches)

va_end(ap) should use in the same func as va_start(). And always in pairs for safety. 
*/
int ft_printf(const char *fmt, ...)
{
    int count;
    int printed_in_spec;
    va_list ap;
    t_fmt_parser f;

    va_start(ap,fmt);
    count = 0;
    while(*fmt && count >= 0)
    {
        if( *fmt != '%')
        {
            if (write_wrapper_in_printf(1, fmt, 1, &count) == -1)
                count = -1;
            fmt++;
            continue;
        }
        if (advance_fmt_isnul(&fmt))
            break;
        printed_in_spec = handle_conversion(ap, &fmt, &f);
        if (printed_in_spec == -1)
            count = -1;
        count += printed_in_spec;
    }
    va_end(ap);
    return count;
}
