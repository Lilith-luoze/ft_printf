#include "ft_printf.h"

int dispatch_parsed(va_list ap, t_fmt_parser f)
{
    if(f.spec == 'c')
        return put_c(va_arg(ap, int), f); // for var_functions, char promoted to int
    else if(f.spec == 's')
        return put_s(va_arg(ap, char *), f);
    else if(f.spec == 'd' || f.spec == 'i')
        return put_d(va_arg(ap, int), f); // fetch ap as int, then move it forward
    else if(f.spec == 'x' ||f.spec == 'X')
        return put_hex(va_arg(ap, unsigned int), f, f.spec == 'X');
    else if (f.spec == 'p')
        return put_p(va_arg(ap, void *), f);
    else if(f.spec == 'u')
        return put_u(va_arg(ap, unsigned int), f);
    else if(f.spec == '%')
        return put_percent(f);
    else // write % and the char at the spec pos as it is
    {
        write(1, "%", 1); // write the '%' character
        return (1 + write(1, &f.spec, 1));     // write the char and return the printed number
    }    
}