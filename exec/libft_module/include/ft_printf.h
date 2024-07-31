/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:36:53 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/06/10 16:54:15 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

# ifdef __linux__
#  define NULLPTR "(nil)"
# elif __APPLE__
#  define NULLPTR "0x0"
# endif

typedef struct s_flags
{
	int	left;
	int	zero;
	int	prec;
	int	hash;
	int	space;
	int	plus;
	int	width;
	int	spec;
}	t_flags;

//Print
int		ft_printf(const char *format, ...);
int		ft_print_format(va_list args, const char format, t_flags *flags);

//Parsing
int		ft_parsing(const char *str, va_list args);
int		ft_parse_flags(const char *str, int i, t_flags *flags);

//Flags
t_flags	ft_init_flags(void);
int		ft_isspec(int c);
int		ft_isflag(int c);
int		ft_isformat(int c);
int		ft_flag_precision(const char *str, int pos, t_flags *flags);
int		ft_pad_width(int width, int size, int zero);

//Find Length
int		ft_hex_len(unsigned int n);
int		ft_uint_len(unsigned int n);
int		ft_ptr_len(unsigned long n);
int		ft_itoa_len(long n);

//Print 'c'
int		ft_print_cf(int c, t_flags *flags);
int		ft_print_char(int c);

//Print 's'
int		ft_print_sf(const char *str, t_flags *flags);
int		ft_print_str(const char *str);
int		ft_print_s_prec(const char *str, int prec);
int		ft_format_str(const char *str, t_flags *flags);

//Print 'p'
int		ft_print_ptrf(unsigned long ptr, t_flags *flags);
int		ft_print_ptr(unsigned long ptr);
void	ft_print_adr(unsigned long n);

//Print 'd' and 'i'
int		ft_print_nbrf(int n, t_flags *flags);
int		ft_print_sign(int n, t_flags *flags);
int		ft_print_nbr(char *str, int n, t_flags *flags);
int		ft_format_nbr(char *str, int n, t_flags *flags);
char	*ft_printf_itoa(long n);

//Print 'u'
int		ft_print_uintf(unsigned int n, t_flags *flags);
int		ft_print_uint(char *str, t_flags *flags);
int		ft_format_uint(char *str, t_flags *flags);
char	*ft_printf_utoa(unsigned int n);

//Print 'x' and 'X'
int		ft_print_hexf(unsigned int n, int format, t_flags *flags);
int		ft_print_hex_prefix(int format);
int		ft_print_hex(char *str, int n, int format, t_flags *flags);
int		ft_format_hex(char *str, int n, int format, t_flags *flags);
char	*ft_printf_xtoa(unsigned int n, int format);

#endif
