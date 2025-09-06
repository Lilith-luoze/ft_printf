#include "ft_printf.h"


// prefix is with new things - 0x or 0X
int put_hex(unsigned int h, t_fmt_parser f, int upper)
{
    t_numcfg n;
    
	n.negative = 0;
	n.un = (unsigned long)h;
	if (n.un == 0)
		f.hash = 0;
	n.prefix_len = decide_prefix(n.negative, f, &n.prefix);
	n.fil_len = utoa_hex_rev(n.un, n.buf, upper);
	n.prec0 = num_prec0(f, &n.fil_len, n.un);
	n.padding = f.width - (n.prefix_len + n.prec0 + n.fil_len);
	if (n.padding < 0)
		n.padding = 0;

	return (put_num_cfg(n, f));
}
