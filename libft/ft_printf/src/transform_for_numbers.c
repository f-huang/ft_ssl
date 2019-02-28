/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_for_numbers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 11:46:12 by fhuang            #+#    #+#             */
/*   Updated: 2017/11/02 19:03:46 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static void		transform_flags(t_print *link, char *str, int len, int neg)
{
	static void	(*p[5])(t_print *link, char *str, int len, int neg);
	int			i;

	neg == 1 ? len-- : 0;
	FLAG[PLUS] ? len-- : 0;
	p[0] = transform_zero;
	p[1] = transform_plus;
	p[2] = transform_space;
	p[3] = transform_hash;
	p[4] = transform_minus;
	PRECISION ? PUSH_FRONT(48, PRECISION - ft_strlen(str)) : 0;
	i = -1;
	while (++i < 5)
		(*p[i])(link, str, len, neg);
	C == 'X' ? ft_strupper(str) : 0;
	neg == 1 ? PUSH_FRONT('-', 1) : 0;
	WIDTH ? PUSH_FRONT(' ', WIDTH - ft_strlen(str)) : 0;
}

static void		get_neg(t_print *link, int *neg)
{
	*neg = 0;
	if ((E_TYPE == T_INT || E_TYPE == T_SHORT || E_TYPE == T_CHAR)\
		&& U_VAR.i < 0)
		*neg = 1;
	else if ((E_TYPE == T_LONG) && U_VAR.l < 0)
		*neg = 1;
	else if (E_TYPE == T_LLONG && U_VAR.ll < 0)
		*neg = 1;
	else if (E_TYPE == T_INMAX && U_VAR.imax < 0)
		*neg = 1;
}

static int		get_len(t_print *link, char *ret, int neg)
{
	int			len;

	if (!ret)
		exit(EXIT_FAILURE);
	len = ft_strlen(ret) + neg;
	LEN = len - neg;
	if (C == 'o' || C == 'O')
		FLAG[HASH] ? len++ : 0;
	else if (C == 'x' || C == 'X')
		FLAG[HASH] ? len += 2 : 0;
	if (FLAG[SPACE] && U_VAR.ull > 0)
		len++;
	len = PRECISION >= len ? PRECISION + neg : len;
	len = WIDTH >= len ? WIDTH + neg : len;
	FLAG[PLUS] ? len++ : 0;
	return (len);
}

static void		get_right_itoa(t_print *link, char **ret, int base, int *neg)
{
	if (U_VAR.uin == 0 && PRECISION == -1)
		*ret = ft_strdup("");
	else if (E_TYPE == T_INT || E_TYPE == T_UIN)
		*ret = (ft_printf_itoa_base(U_VAR.uin, base, E_TYPE == T_INT ?\
			0 : 1));
	else if (E_TYPE == T_SHORT || E_TYPE == T_USHORT)
		*ret = (ft_stoa_base(U_VAR.i, base, E_TYPE == T_SHORT ?\
			0 : 1, neg));
	else if (E_TYPE == T_CHAR || E_TYPE == T_UCHAR)
		*ret = (ft_ctoa_base(U_VAR.i, base, E_TYPE == T_CHAR ?\
			0 : 1, neg));
	else if (E_TYPE == T_LONG || E_TYPE == T_ULONG)
		*ret = (ft_ltoa_base(U_VAR.l, base, E_TYPE == T_LONG ? 0 : 1));
	else
		*ret = (ft_lltoa_base(U_VAR.ll, base,\
			(E_TYPE == T_LLONG || E_TYPE == T_INMAX) ? 0 : 1));
	if (*ret == NULL)
		exit(EXIT_FAILURE);
}

void			transform_for_numbers(t_print *link)
{
	char		*ret;
	int			len;
	int			base;
	int			neg;

	ret = NULL;
	base = 10;
	if (C == 'o' || C == 'O')
		base = 8;
	else if (C == 'x' || C == 'X')
		base = 16;
	else if (C == 'b')
		base = 2;
	get_neg(link, &neg);
	get_right_itoa(link, &ret, base, &neg);
	len = get_len(link, ret, neg);
	if ((RET = ft_strndup(ret, len)) == NULL)
		exit(EXIT_FAILURE);
	ft_strdel(&ret);
	transform_flags(link, RET, len, neg);
}
