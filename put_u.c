#include "ft_printf.h"


int put_u(unsigned int u, t_fmt_parser f)
{
	t_numcfg n;

	n.negative = 0;
	n.prefix_len = 0;
	n.un = (unsigned long)u;
	n.fil_len = utoa_dec_rev(n.un, n.buf);
	n.prec0 = num_prec0(f, &n.fil_len, n.un);
	n.padding = f.width - (n.prefix_len + n.prec0 + n.fil_len);
	if (n.padding < 0)
		n.padding = 0;

	return (put_num_cfg(n, f));
}
