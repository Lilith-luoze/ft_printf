#ifndef LOCAL_PRINTF_H
# define LOCAL_PRINTF_H

# include <stdarg.h> // for variable argument lists (va_list, va_start, va_end)
# include <unistd.h> // for write()

typedef struct s_fmt {
    int minus;    // '-' flag (0/1)
    int zero;    // '0' flag (0/1)
    
    int width;   // -1 if not set
    int prec;    // -1 if not set

    char spec;   // c s p d i u x X %


    int space;   // ' ' flag (0/1)
    int hash;   // '#' flag (0/1) 
    int plus;    // '+' flag (0/1)
} t_fmt_parser;

typedef struct s_num
{
	unsigned long	un;         // absolute value of the number
	int				negative;   // 1 if original number < 0
	char			buf[32];    // digits in reverse
	int				fil_len;    // digit length
	int				prec0;     // extra leading zeros from precision
	char*			prefix;     //
	int				prefix_len; 
	int				padding;    // spaces/zeros for width
}	t_numcfg;


# if defined(__linux__)
# define NULL_PTR "(nil)"
# elif defined(__APPLE__)
# define NULL_PTR "0x0"
# endif

// utility1.c
int put_repeat(char r, int len);
int utoa_dec_rev(unsigned int u, char *buf);
int put_buffer_rev(char *buf, int len);
int decide_prefix(int negative, t_fmt_parser f, char **prefix_pp);

// utility2.c
int itoul(int n, unsigned long *un);
int num_prec0(t_fmt_parser f, int *fil_len, unsigned long un);
int put_num_cfg(t_numcfg n, t_fmt_parser f);
int utoa_hex_rev(unsigned long u, char *buf, int upper);
size_t ft_strlen(const char *s);

//parser.c
void parser_init(t_fmt_parser *f);
int parse_number(const char **fmt);
const char *parse_fmt_main(const char *fmt, t_fmt_parser *f_p);
void parse_fmt_normalize(t_fmt_parser *f_p);

// dispatcher.c
int dispatch_parsed(va_list ap, t_fmt_parser f);

// put %c s d u x X p %

int put_c(int c, t_fmt_parser f);
int put_s(char *s, t_fmt_parser f);
int put_d(int d, t_fmt_parser f);
int put_u(unsigned int u, t_fmt_parser f);
int put_hex(unsigned int u, t_fmt_parser f, int upper);
int put_p(void *p, t_fmt_parser f);
int put_percent(t_fmt_parser f);



#endif
