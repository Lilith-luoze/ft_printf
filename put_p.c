#include "local_printf.h"


int put_p(void *p, t_fmt_parser f)
{
    t_numcfg n;
    
	n.negative = 0;
	n.prefix_len = 2;
	n.prefix = "0x";
	n.un = (unsigned long)p;
	n.fil_len = utoa_hex_rev(n.un, n.buf, 0);
	n.prec0 = num_prec0(f, &n.fil_len, n.un);
	n.padding = f.width - (n.prefix_len + n.prec0 + n.fil_len);
	if (n.padding < 0)
		n.padding = 0;

	return (put_num_cfg(n, f));
}
