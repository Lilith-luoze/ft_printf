#include "ft_printf.h"

/// @brief  find char c in string s
/// @param s 
/// @param c 
/// @return  1 if found, 0 if not found
int ft_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return 1;
        s++;
    }
    if (c == '\0' && *s == '\0')
        return 1;
    return 0;
}

/*bonus rule 2: 
plus is to add sign.
space is to prepend a space if no sign is added
hash is to add prefix, or alternate form. */
// parse fmt function - 4 steps
// this is strictly the sequence; if it can't reach the legitimate spec, it will go back and print as literal
const char * parse_fmt(const char *fmt, t_fmt_parser *f_p )
{
    const char *start;
    const char *lawful_specs;

    lawful_specs = "cspdiuxX%";
    start = fmt;
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
    if (*fmt == '\0')
    {
        f_p->spec = '%'; 
    }
    else if (ft_strchr(lawful_specs, *fmt))
    {
        f_p->spec = *fmt;
        fmt++;
    }
    else // the case where should go back to print the literal, i want to keep the case 
    {
        f_p -> if_ltr_percent = 1; // indicate a literal % is needed to print and passed
        return start;
    }
        
    return fmt;        // don't move beyond \0
}

void parser_init(t_fmt_parser *f) 
{
    f->minus= 0;
    f->zero= 0;
    f->plus=0;
    f->space=0;
    f->hash=0;
    f->width = -1; 
    f->prec = -1; 
    f->spec = 0;
    f -> if_ltr_percent = 0;
}

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
    if (f_p -> spec == '%')
    {
        f_p->plus = 0;
        f_p->space = 0;
        f_p->hash = 0;
    }
}