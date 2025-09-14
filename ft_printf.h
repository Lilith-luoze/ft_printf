/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:43:20 by luozguo           #+#    #+#             */
/*   Updated: 2025/09/14 19:57:48 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h> // for variable argument lists (va_list, va_start, va_end)
# include <stdlib.h> // for malloc and free()
# include <unistd.h> // for write()

/// @brief most of members are set 0 by init. Only width, prec are -1 by init
typedef struct s_fmt
{
	int				minus;
	int				zero;
	int				space;
	int				hash;
	int				plus;
	int				if_ltr_percent;
	char			spec;

	int				width;
	int				prec;
}					t_fmt_parser;

/// @brief
/// @param buf  digits in reverse
/// @param fil_len digit length
/// @param prec0   extra leading zeros from precision
typedef struct s_num
{
	unsigned long	un;
	int				negative;
	char			buf[32];
	int				fil_len;
	int				prec0;
	char			*prefix;
	int				prefix_len;
	int				padding;
}					t_numcfg;

// when spec p , arg is NULL, print (nil) in linux, 0x0 in mac
# if defined(__linux__)
#  define NULL_PTR "(nil)"
# elif defined(__APPLE__)
#  define NULL_PTR "0x0"
# endif

void				iterator_in_printf(va_list *ap, const char **fmt,
						t_fmt_parser *f, int *count);
int					ft_printf(const char *fmt, ...);
int					handle_conversion(va_list *ap, const char **fmt,
						t_fmt_parser *f);
int					advance_fmt_isnul(const char **fmt);
void				literal_write_handler(const char **fmt, int *count,
						t_fmt_parser *f);
int					write_with_copying_adding_0(int fd, int ori_len,
						const char *s);
int					strlen_til_percent(const char *s);

// put_helpers_1.c
int					put_repeat(char r, int len, int *err_flag);
int					utoa_dec_rev(unsigned int u, char *buf);
int					put_buffer_rev(char *buf, int len, int *err_flag);
int					decide_prefix_for_dx(int negative, t_fmt_parser f,
						char **prefix_pp);
int					write_wrapper(int fd, const void *buf, size_t len,
						int *err_flag);

// put_helpers_2.c
int					itoul(int n, unsigned long *un);
int					num_prec0(t_fmt_parser f, int *fil_len, unsigned long un);
int					put_num_cfg(t_numcfg n, t_fmt_parser f);
int					utoa_hex_rev(unsigned long u, char *buf, int upper);
size_t				ft_strlen(const char *s);

// parser.c
void				parser_init(t_fmt_parser *f);
int					parse_number(const char **fmt);
const char			*parse_fmt(const char *fmt, t_fmt_parser *f_p);
void				parse_fmt_normalize(t_fmt_parser *f_p);

// dispatcher.c
int					dispatch_parsed(va_list *ap, t_fmt_parser f);

// put %c s d u x X p %

int					put_c(int c, t_fmt_parser f);
int					put_s(char *s, t_fmt_parser f);
int					put_d(int d, t_fmt_parser f);
int					put_u(unsigned int u, t_fmt_parser f);
int					put_hex(unsigned int u, t_fmt_parser f, int upper);
int					put_p(void *p, t_fmt_parser f);
int					put_percent(t_fmt_parser f);
int					put_num_cfg_left(t_numcfg n, int *err_flag);

#endif
