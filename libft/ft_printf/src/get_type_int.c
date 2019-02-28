/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 21:17:02 by fhuang            #+#    #+#             */
/*   Updated: 2016/06/29 15:28:38 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		modifier_z(t_print *link, char type)
{
	if (type == 'i' || type == 'd')
		E_TYPE = T_LONG;
	else
		E_TYPE = T_ULONG;
}

static void		modifier_j(t_print *link, char type)
{
	if (type == 'i' || type == 'd')
		E_TYPE = T_INMAX;
	else
		E_TYPE = T_UINMAX;
}

static void		modifier_l(t_print *link, int *modifier, char type)
{
	if (modifier[1] == 1)
	{
		if (type == 'i' || type == 'd')
			E_TYPE = T_LONG;
		else
			E_TYPE = T_ULONG;
	}
	else
	{
		if (type == 'i' || type == 'd')
			E_TYPE = T_LLONG;
		else
			E_TYPE = T_ULLONG;
	}
}

static void		modifier_h(t_print *link, int *modifier, char type)
{
	if (modifier[0] == 1)
	{
		if (type == 'i' || type == 'd')
			E_TYPE = T_SHORT;
		else
			E_TYPE = T_USHORT;
	}
	else
	{
		if (type == 'i' || type == 'd')
			E_TYPE = T_CHAR;
		else
			E_TYPE = T_UCHAR;
	}
}

void			get_type_int(t_print *link, int *modifier, char type)
{
	if (modifier[1])
		modifier_l(link, modifier, type);
	else if (modifier[2])
		modifier_j(link, type);
	else if (modifier[3])
		modifier_z(link, type);
	else if (modifier[0])
		modifier_h(link, modifier, type);
	else
		E_TYPE = (type == 'i' || type == 'd') ? T_INT : T_UIN;
}
