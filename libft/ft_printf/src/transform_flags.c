/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 16:23:09 by fhuang            #+#    #+#             */
/*   Updated: 2017/10/19 11:48:50 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		transform_plus(t_print *link, char *str, int len, int neg)
{
	if (FLAG[PLUS] == 0)
		return ;
	neg == 0 || U_VAR.i == 0 ? PUSH_FRONT('+', 1) : 0;
	(void)len;
}

void		transform_space(t_print *link, char *str, int len, int neg)
{
	if (FLAG[SPACE] == 0)
		return ;
	neg == 0 ? PUSH_FRONT(' ', 1) : 0;
	(void)len;
}

void		transform_hash(t_print *link, char *str, int len, int neg)
{
	if (FLAG[HASH] == 0)
		return ;
	if ((C == 'o' || C == 'O') && ((((size_t)PRECISION > ft_strlen(str) || \
		(PRECISION == 0)) && U_VAR.ull != 0) ||\
		(PRECISION < 0 && U_VAR.ull == 0)))
		PUSH_FRONT(48, 1);
	else if (((C == 'x' || C == 'X') && U_VAR.ull != 0) || (C == 'p'))
	{
		PUSH_FRONT('x', 1);
		PUSH_FRONT(48, 1);
	}
	(void)len;
	(void)neg;
}

void		transform_minus(t_print *link, char *str, int len, int neg)
{
	if (FLAG[MINUS] == 0)
		return ;
	PUSH_BACK(' ', len - ft_strlen(str) - neg);
	(void)neg;
}

void		transform_zero(t_print *link, char *str, int len, int neg)
{
	int		n;

	if (FLAG[ZERO] == 0)
		return ;
	n = len - ft_strlen(str) - neg;
	if (FLAG[HASH] && (C == 'o' || C == 'O'))
		n--;
	else if (FLAG[HASH] && (((C == 'x' || C == 'X') && U_VAR.ull != 0) ||\
		(C == 'p')))
		n -= 2;
	((FLAG[PLUS] && neg == 0) || FLAG[SPACE]) ? n-- : 0;
	PUSH_FRONT(48, n);
}
