/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 23:31:30 by fhuang            #+#    #+#             */
/*   Updated: 2017/10/20 14:36:38 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

void		destroy_env(t_printf_tools *e)
{
	t_print		*link;
	t_print		*tmp;

	link = e->full_lst;
	while (link)
	{
		tmp = link;
		link = NEXT;
		if (tmp->transformed_str != NULL)
			free(tmp->transformed_str);
		if (tmp != NULL)
			free(tmp);
		ft_bzero(tmp, sizeof(t_print));
	}
	init_env(e);
}

void		init_env(t_printf_tools *e)
{
	e->full_lst = NULL;
	e->arg_lst = NULL;
}
