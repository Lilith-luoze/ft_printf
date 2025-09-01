# include "local_printf.h"

/// @brief Put decimal number to stdout, return number of characters written
// handles sign, precision (leading zeros), width, and flags (+, space, 0, -).
// prec never truncates digits
int	put_d(int d, t_fmt_parser f)
{
	t_numcfg n;

	n.negative = itoul(d, &n.un);
	n.fil_len = utoa_dec_rev(n.un, n.buf);
	n.prec0 = num_prec0(f, &n.fil_len, n.un);
	n.prefix_len = decide_prefix(n.negative, f, &(n.prefix));
	n.padding = f.width - (n.prefix_len + n.prec0 + n.fil_len);
	if (n.padding < 0)
		n.padding = 0;

	return (put_num_cfg(n, f));
}


