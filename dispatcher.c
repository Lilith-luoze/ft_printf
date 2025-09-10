#include "ft_printf.h"

int dispatch_parsed(va_list *ap, t_fmt_parser f)
{
    int err_flag;
    err_flag = 0;

    if(f.spec == 'c')
        return put_c(va_arg(*ap, int), f); // for var_functions, char promoted to int
    else if(f.spec == 's')
        return put_s(va_arg(*ap, char *), f);
    else if(f.spec == 'd' || f.spec == 'i')
        return put_d(va_arg(*ap, int), f); // fetch ap as int, then move it forward
    else if(f.spec == 'x' ||f.spec == 'X')
        return put_hex(va_arg(*ap, unsigned int), f, f.spec == 'X');
    else if (f.spec == 'p')
        return put_p(va_arg(*ap, void *), f);
    else if(f.spec == 'u')
        return put_u(va_arg(*ap, unsigned int), f);
    else if(f.spec == '%')
        return put_percent(f);
    else // write % and the char at the spec pos as it is
    {
        write_wrapper(1, "%", 1, &err_flag);
        write_wrapper(1, &f.spec, 1, &err_flag);
        if (err_flag)
            return -1;
        return (2);
    }    
}
