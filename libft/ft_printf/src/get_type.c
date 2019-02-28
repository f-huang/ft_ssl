/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 20:42:23 by fhuang            #+#    #+#             */
/*   Updated: 2016/06/29 15:28:32 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		get_type_str_or_point(t_print *link, int *modifier, char type)
{
	if (type == 's')
		E_TYPE = modifier[1] ? T_WSTR : T_STR;
	else if (type == 'c')
		E_TYPE = modifier[1] ? T_WCHAR : T_CHAR;
	else if (type == 'p')
		E_TYPE = T_VOID;
}

int				get_type(t_print *link, int *modifier, char type)
{
	int			i;

	C = type;
	if (type >= 'A' && type < 'X')
	{
		modifier[1]++;
		type += 32;
	}
	i = -1;
	while (TYPES_PAT[++i])
		if (TYPES_PAT[i] == type)
			i >= 3 && i <= 12 ? get_type_int(link, modifier, type) :\
				get_type_str_or_point(link, modifier, type);
	return (0);
}
