/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desactivate_flags.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 20:41:36 by fhuang            #+#    #+#             */
/*   Updated: 2016/10/28 17:28:37 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			desactivate_hash_key(t_print *link, char type)
{
	const char	s1[] = "cdips";
	int			i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == type)
			FLAG[HASH] = 0;
		i++;
	}
}

static void			desactivate_zero(t_print *link, char type)
{
	const char	s2[] = "dibopuxX";
	int			i;

	i = 0;
	while (s2[i])
	{
		if (FLAG[MINUS] == 1 || (PRECISION && s2[i] == type))
			FLAG[ZERO] = 0;
		i++;
	}
}

static void			desactivate_space(t_print *link, char type)
{
	if (FLAG[PLUS] == 1 && FLAG[SPACE] == 1)
		FLAG[SPACE] = 0;
	if (type != 'i' && type != 'd')
		FLAG[SPACE] = 0;
}

static void			desactivate_plus(t_print *link, char type)
{
	if (type != 'i' && type != 'd')
		FLAG[PLUS] = 0;
}

void				desactivate_flags(t_print *link, char type)
{
	if (FLAG[0] == 1)
		desactivate_hash_key(link, type);
	if (FLAG[1] == 1)
		desactivate_zero(link, type);
	desactivate_plus(link, type);
	desactivate_space(link, type);
	if (type == 'p')
		FLAG[HASH] = 1;
}
