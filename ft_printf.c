#include "ft_printf.h"

int	strlen_til_percent(const char *s)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != '%' && s[len] != '\0')
		len++;
	return (len);
}

/// @brief advance fmt pointer by 1, if it reaches null, return 1
/// @param fmt
/// @return
int	advance_fmt_isnul(const char **fmt)
{
	*fmt += 1;
	if (**fmt == '\0')
		return (1);
	return (0);
}

/// @brief process one conversion specifier
/// @param ap
/// @param fmt
/// @param f
/// @return number of printed characters, or -1 on error
int	handle_conversion(va_list *ap, const char **fmt, t_fmt_parser *f)
{
	parser_init(f);
	*fmt = parse_fmt(*fmt, f);
	if (f->if_ltr_percent)
		return (0);
	parse_fmt_normalize(f);
	return (dispatch_parsed(ap, *f));
}

void	iterator_in_printf(va_list *ap, const char **fmt, t_fmt_parser *f,
		int *count)
{
	int	printed_in_spec;

	while (**fmt && (*count) >= 0)
	{
		if ((**fmt) != '%')
		{
			literal_write_handler(fmt, count, f);
			continue ;
		}
		if (advance_fmt_isnul(fmt))
			break ;
		printed_in_spec = handle_conversion(ap, fmt, f);
		if (printed_in_spec == -1)
			(*count) = -1;
		else
			(*count) += printed_in_spec;
	}
}

/*
- write func to check for wrong return (check all the way to each branches)

va_end(ap) should use in the same func as va_start(). And always in pairs for safety.
*/
int	ft_printf(const char *fmt, ...)
{
	int				count;
	va_list			ap;
	t_fmt_parser	f;

	va_start(ap, fmt);
	count = 0;
	parser_init(&f);
	iterator_in_printf(&ap, &fmt, &f, &count);
	va_end(ap);
	return (count);
}
