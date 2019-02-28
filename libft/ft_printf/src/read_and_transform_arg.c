/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_transform_arg.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 22:56:34 by fhuang            #+#    #+#             */
/*   Updated: 2017/10/20 14:36:50 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define VA_ARG(x) va_arg(*ap, x)

void		get_variable2(t_print *link, va_list *ap)
{
	if (E_TYPE == T_INT || E_TYPE == T_SHORT || E_TYPE == T_USHORT ||\
		E_TYPE == T_CHAR || E_TYPE == T_UCHAR)
		U_VAR.i = VA_ARG(int);
	else if (E_TYPE == T_UIN)
		U_VAR.uin = VA_ARG(unsigned int);
	else if (E_TYPE == T_INMAX)
		U_VAR.imax = VA_ARG(intmax_t);
	else if (E_TYPE == T_UINMAX)
		U_VAR.uinmax = VA_ARG(uintmax_t);
	else if (E_TYPE == T_LONG)
		U_VAR.l = VA_ARG(long);
	else if (E_TYPE == T_LLONG)
		U_VAR.ll = VA_ARG(long long);
	else if (E_TYPE == T_ULONG)
		U_VAR.ul = VA_ARG(unsigned long);
	else if (E_TYPE == T_ULLONG)
		U_VAR.ull = VA_ARG(unsigned long long);
}

void		get_variable(t_print *link, va_list *ap)
{
	if (E_TYPE == T_CHAR && C == 'c')
		U_VAR.i = VA_ARG(int);
	else if (E_TYPE == T_WCHAR)
		U_VAR.wc = VA_ARG(wchar_t);
	else if (E_TYPE == T_STR)
		U_VAR.s = VA_ARG(char *);
	else if (E_TYPE == T_WSTR)
		U_VAR.ws = VA_ARG(wchar_t*);
	else if (E_TYPE == T_VOID)
		U_VAR.p = VA_ARG(void *);
	else
	{
		get_variable2(link, ap);
		transform_for_numbers(link);
		return ;
	}
	transform_for_strings(link);
}

void		read_and_transform_arg(t_printf_tools *e)
{
	t_print		*link;

	link = e->arg_lst;
	while (link)
	{
		if (ft_strchr(TYPES_PAT, C))
			get_variable(link, &e->ap);
		else
			no_type_conversion(link);
		link = NEXT_ARG;
	}
}
