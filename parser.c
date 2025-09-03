#include "local_printf.h"

void parser_init(t_fmt_parser *f) 
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
const char * parse_fmt_main(const char *fmt, t_fmt_parser *f_p)
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
        f_p -> prec = 0;
        if (fmt++, *fmt >= '0' && *fmt <= '9')
            f_p -> prec = parse_number(&fmt);
    }
    // 4) specifer 
    if (*fmt != '\0')
        f_p -> spec = *fmt;
    else
        f_p -> spec = '%';
    return (fmt++);
}

// deal with flag conflicts
/* override rules; normalize */
void parse_fmt_normalize(t_fmt_parser *f_p)
{
    if (f_p->minus) 
        f_p->zero = 0;
    if (f_p->plus)  
        f_p->space = 0;
    if (f_p->prec != -1)
        f_p->zero = 0; 
}