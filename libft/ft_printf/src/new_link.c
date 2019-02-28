/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 22:48:56 by fhuang            #+#    #+#             */
/*   Updated: 2017/10/20 14:36:58 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

int		new_link(t_printf_tools *e, char *str, char *type, int arg)
{
	t_print		*new;

	if (!(new = (t_print*)ft_memalloc(sizeof(t_print))))
		exit(EXIT_FAILURE);
	if (arg == 0)
	{
		if ((new->transformed_str = ft_strndup(str, (int)(type - str))) == NULL)
			exit(EXIT_FAILURE);
		new->len = ft_strlen(new->transformed_str);
	}
	else
	{
		if ((get_struct(new, str, *type, -1)) == -1)
			return (-1);
	}
	add_link(e, new, arg);
	return (0);
}
