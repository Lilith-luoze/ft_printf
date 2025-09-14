/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_helpers_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:12:33 by luozguo           #+#    #+#             */
/*   Updated: 2025/09/14 19:32:27 by luozguo          ###   ########.fr       */
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

int	write_with_copying_adding_0(int fd, int ori_len, const char *s)
{
	int		ret;
	int		i_str_with_0;
	int		i_s;
	char	*str_with_0;
	int		first_dot;

	first_dot = 1;
	i_str_with_0 = 0;
	i_s = 0;
	str_with_0 = (char *)malloc(ori_len + 1);
	if (!str_with_0)
		return (-1);
	while (i_s < ori_len)
	{
		str_with_0[i_str_with_0++] = s[i_s];
		if (s[i_s] == '.' && first_dot)
		{
			str_with_0[i_str_with_0++] = '0';
			first_dot = 0;
		}
		i_s++;
	}
	ret = write(fd, str_with_0, ori_len + 1);
	free(str_with_0);
	return (ret);
}

/// @brief first compute the number of non-percent literals and write them,
///	and advance according fmt pointer for printf(); or if_ltr_percent is 1,
///	go back one fmt and write ltr_fmt + 1 chars (extra literal % ), and advance
/// fmt pointers. Always change count, printed_chars or on write error,
///	set count to -1.
/// @param fmt
/// @param count
/// @param f
/// @return nothing
void	literal_write_handler(const char **fmt, int *count, t_fmt_parser *f)
{
	int	fd;
	int	ltr_len;
	int	temp;

	fd = 1;
	ltr_len = strlen_til_percent(*fmt);
	if (f->if_ltr_percent)
	{
		if (f->prec == 0 && f->spec == 0)
			temp = write_with_copying_adding_0(fd, ltr_len + 1, (*fmt) - 1);
		else
			temp = write(fd, (*fmt) - 1, ltr_len + 1);
		f->if_ltr_percent = 0;
		(*fmt) += ltr_len;
	}
	else
	{
		temp = write(fd, *fmt, ltr_len);
		(*fmt) += ltr_len;
	}
	if (temp == -1)
		*count = -1;
	else
		*count += temp;
}
