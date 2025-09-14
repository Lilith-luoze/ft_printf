/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_p.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:43:45 by luozguo           #+#    #+#             */
/*   Updated: 2025/09/14 16:43:46 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void decide_prefix_for_p(t_fmt_parser f, char **prefix, int *prefix_len)
{
	if (f.space)
	{
		*prefix = " 0x";
		*prefix_len = 3;
	}
	else if (f.plus)
	{
		*prefix = "+0x";
		*prefix_len = 3;
	}
	else
	{
		*prefix = "0x";
		*prefix_len = 2;
	}
}


int put_p(void *p, t_fmt_parser f)
{
    t_numcfg n;

    if (p == NULL)
		return (put_s(NULL_PTR, f));
	n.negative = 0;
	decide_prefix_for_p(f, &n.prefix, &n.prefix_len);
	n.un = (unsigned long)p;
	n.fil_len = utoa_hex_rev(n.un, n.buf, 0);
	n.prec0 = num_prec0(f, &n.fil_len, n.un);
	n.padding = f.width - (n.prefix_len + n.prec0 + n.fil_len);
	if (n.padding < 0)
		n.padding = 0;

	return (put_num_cfg(n, f));
}
