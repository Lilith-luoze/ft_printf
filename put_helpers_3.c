/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_helpers_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:12:33 by luozguo           #+#    #+#             */
/*   Updated: 2025/09/14 19:14:23 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	parser_init(t_fmt_parser *f)
{
	f->minus = 0;
	f->zero = 0;
	f->plus = 0;
	f->space = 0;
	f->hash = 0;
	f->width = -1;
	f->prec = -1;
	f->spec = 0;
	f->if_ltr_percent = 0;
}

// parse number and move the fmt pointer at the same time,
//	it would points to place that not ever been treated.
int	parse_number(const char **fmt)
{
	int	result;

	result = 0;
	while (**fmt >= '0' && **fmt <= '9')
	{
		result = result * 10 + (**fmt - '0');
		(*fmt)++;
	}
	return (result);
}
