#include "local_printf.h"
#include "public_printf.h"


void parser_init(t_fmt *f) 
{
    f->minus=f->zero=f->plus=f->space=f->hash=0;
    f->width = -1; f->prec = -1; f->spec = 0;
}

/* parse *fmt in a fixed order:
Flags loop.

Width loop.

Precision loop.

Specifier.*/

// parse number and move the fmt pointer at the same time, it would points to place that not ever been treated.
int parse_number(const char **fmt)
{
    int result = 0;
    while(**fmt >= '0' && **fmt <= '9')
    {
        result = result * 10 + (**fmt - '0');
        (*fmt)++;
    }
    return (result);
}
/*bonus rule 2: 
plus is to add sign.
    space is to prepend a space if no sign is added
hash is to add prefix, or alternate form. */
// parse fmt function - 4 steps
const char * parse_fmt_1(const char *fmt, t_fmt *f_p)
{
    // parse 1) flags: - 0 # + space,
    while (*fmt == '-' || *fmt == '0' || *fmt == '#' || *fmt == '+' || *fmt == ' ')
    {
        if (*fmt == '-') f_p->minus = 1;
        if (*fmt == '0') f_p->zero  = 1;
        if (*fmt == '#') f_p->hash  = 1;  
        if (*fmt == '+') f_p->plus  = 1;
        if (*fmt == ' ') f_p->space = 1;
        fmt++;
    }
    // 2) width,
    if (*fmt >= '0' && *fmt <= '9')
        f_p -> width = parse_number(&fmt);
    // 3) precision,
    if (*fmt == '.')
    {
        fmt++;
        f_p -> prec = 0;
        if (*fmt >= '0' && *fmt <= '9')
            f_p -> prec = parse_number(&fmt);
    }
    // 4) specifer (loose control here; identifying it later) ?? what if a null ter.
    f_p -> spec = *fmt;
    fmt++;
    return fmt;
}

// deal with flag conflicts
/* override rules; normalize */
const char * parse_fmt_2(t_fmt *f_p)
{
    if (f_p->minus) 
        f_p->zero = 0;
    if (f_p->plus)  
        f_p->space = 0;
    if (f_p->prec != -1 && (f_p->spec=='d'||f_p->spec=='i'
        ||f_p->spec=='u'||f_p->spec=='x'||f_p->spec=='X'))
        f_p->zero = 0;

}

int dispatch_parsed(va_list ap, t_fmt f)
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
        return write(1, "%", 1);
    else // write % and the char at the spec pos as it is
    {
        write(1, "%", 1); // write the '%' character
        return (1 + write(1, &f.spec, 1));     // write the char and return the printed number
    }    
}

int handle_format(const char **fmt_pp, va_list ap, t_fmt *f_p)
{
    if (**fmt_pp == '\0')
        return (0);
    *fmt_pp = parse_fmt_1(*fmt_pp, f_p); // renewed the fmt pointer
    *fmt_pp = parse_fmt_2(*fmt_pp, f_p); // renewed the fmt pointer
    if (**fmt_pp == '\0')
        return (0);
    return (dispatch_parsed(ap , *f_p));
}

int ft_printf(const char *fmt, ...)
{
    int count;
    va_list ap;
    t_fmt f;

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
        else
        {
            fmt++;
            count += handle_format(&fmt, ap, &f);
            if (*fmt == '\0')
                break;
            fmt++; //??
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

