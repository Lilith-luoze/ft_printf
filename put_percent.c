/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_percent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:43:47 by luozguo           #+#    #+#             */
/*   Updated: 2025/09/14 16:43:48 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_percent(t_fmt_parser f)
{
	int	count;
int	err_flag;

	count = 0;
	err_flag = 0;
	
	if (f.minus)
	{
		count += write_wrapper(1, "%", 1, &err_flag);
		count += put_repeat(' ', f.width - 1, &err_flag);
	}
	else
	{
		if (f.zero)
			count += put_repeat('0', f.width - 1, &err_flag);
		else
			count += put_repeat(' ', f.width - 1, &err_flag);
		count += write_wrapper(1, "%", 1, &err_flag);
	}
if (err_flag)
		return -1;
	return (count);
}
