/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:43:28 by luozguo           #+#    #+#             */
/*   Updated: 2025/09/14 19:55:29 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/// @brief  find char c in string s
/// @param s
/// @param c
/// @return  1 if found, 0 if not found
int	ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return (1);
		s++;
	}
	if (c == '\0' && *s == '\0')
		return (1);
	return (0);
}

/*bonus rule 2:
plus is to add sign.
space is to prepend a space if no sign is added
hash is to add prefix, or alternate form. */
// parse fmt function - 4 steps
// this is strictly the sequence; if it can't reach the legitimate spec,
//	it will go back and print as literal

const char	*parse_fmt_1_prefix(t_fmt_parser *f_p, const char *fmt)
{
	while (*fmt == '-' || *fmt == '0' || *fmt == '#' || *fmt == '+'
		|| *fmt == ' ')
	{
		if (*fmt == '-')
			f_p->minus = 1;
		if (*fmt == '0')
			f_p->zero = 1;
		if (*fmt == '#')
			f_p->hash = 1;
		if (*fmt == '+')
			f_p->plus = 1;
		if (*fmt == ' ')
			f_p->space = 1;
		fmt++;
	}
	return (fmt);
}

const char	*parse_fmt_2_3_width_prec(t_fmt_parser *f_p, const char *fmt)
{
	if (*fmt >= '0' && *fmt <= '9')
		f_p->width = parse_number(&fmt);
	if (*fmt == '.')
	{
		f_p->prec = 0;
		fmt++;
		if (*fmt >= '0' && *fmt <= '9')
			f_p->prec = parse_number(&fmt);
	}
	return (fmt);
}

const char	*parse_fmt(const char *fmt, t_fmt_parser *f_p)
{
	const char	*start;
	const char	*lawful_specs;

	lawful_specs = "cspdiuxX%";
	start = fmt;
	fmt = parse_fmt_1_prefix(f_p, fmt);
	fmt = parse_fmt_2_3_width_prec(f_p, fmt);
	if (*fmt == '\0')
	{
		f_p->spec = '%';
	}
	else if (ft_strchr(lawful_specs, *fmt))
	{
		f_p->spec = *fmt;
		fmt++;
	}
	else
	{
		f_p->if_ltr_percent = 1;
		return (start);
	}
	return (fmt);
}

// deal with flag conflicts
/* override rules; normalize */
void	parse_fmt_normalize(t_fmt_parser *f_p)
{
	if (f_p->minus)
		f_p->zero = 0;
	if (f_p->plus)
		f_p->space = 0;
	if (f_p->prec != -1)
		f_p->zero = 0;
	if (f_p->spec == '%')
	{
		f_p->plus = 0;
		f_p->space = 0;
		f_p->hash = 0;
	}
}
