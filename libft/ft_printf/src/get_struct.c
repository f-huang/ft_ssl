/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 22:46:11 by fhuang            #+#    #+#             */
/*   Updated: 2017/10/19 11:48:46 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_modifier(int *modifier, char c)
{
	int		i;

	i = 0;
	while (MODIFIERS_PAT[i])
	{
		if (c == MODIFIERS_PAT[i])
		{
			if (modifier[i] < 2)
				modifier[i]++;
			return (0);
		}
		++i;
	}
	return (-1);
}

static int	get_flag(t_print *link, char c)
{
	int		i;

	i = 0;
	while (FLAGS_PAT[i])
	{
		if (c == FLAGS_PAT[i])
		{
			FLAG[i] = 1;
			return (0);
		}
		i++;
	}
	return (-1);
}

static int	get_precision_or_width(t_print *link, char *ptr, char type,\
				int p)
{
	if (p == 1)
	{
		PRECISION = ft_atoi(ptr);
		if (type == 's' && PRECISION == 0)
		{
			while (*ptr && (*ptr == '-' || *ptr == '+'))
				ptr++;
			if (*ptr == '0')
				PRECISION = -1;
		}
		if (PRECISION == 0)
			PRECISION = -1;
		return (ft_nbrlen(PRECISION));
	}
	if (WIDTH == 0)
	{
		WIDTH = ft_atoi(ptr);
		return (ft_nbrlen(WIDTH));
	}
	return (ft_nbrlen(ft_atoi(ptr)));
}

int			get_struct(t_print *link, char *str, char type, int i)
{
	int		tmp;
	char	*ptr;
	int		modifier[4];

	ptr = str;
	ft_bzero(modifier, sizeof(int) * 4);
	while (str[++i] && str[i] != type && (tmp = 0) == 0)
		if ((get_flag(link, str[i])) == -1)
		{
			if (ft_isdigit(str[i]))
				(tmp = get_precision_or_width(link, str + i, type, 0)) != 0\
					? i += tmp : 0;
			if (type != '.' && str[i] == '.' && (tmp = 0) == 0)
			{
				if ((i += get_precision_or_width(link, str + i + 1, type,\
					1)) && str[i] == type)
					break ;
			}
			else if (str[i] != type && ft_strchr(FLAGS_PAT, str[i]) == 0 &&\
				(get_modifier(modifier, str[i])) == -1)
				return (-1);
			tmp ? i-- : 0;
		}
	desactivate_flags(link, type);
	return (get_type(link, modifier, type));
}
