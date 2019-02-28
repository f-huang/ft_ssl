/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 13:32:13 by fhuang            #+#    #+#             */
/*   Updated: 2017/11/02 19:03:54 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*no_type(t_printf_tools *e, char *str)
{
	char	*ptr;

	ptr = str;
	if (*ptr == '^')
	{
		new_link(e, str, ++ptr, 0);
		return (ptr);
	}
	while (*ptr && (ft_isdigit(*ptr) || *ptr == '.' ||\
		ft_strchr(FLAGS_PAT, *ptr) || ft_strchr(MODIFIERS_PAT, *ptr)))
		ptr++;
	if (*ptr == '\0')
	{
		return (ptr);
	}
	new_link(e, str, ptr, 1);
	return (++ptr);
}

static int		check_for_percentage(t_printf_tools *e, char *str)
{
	if (*str && *str == '%')
	{
		new_link(e, (str - 1), str, 0);
		return (1);
	}
	return (0);
}

static char		*parse_format(t_printf_tools *e, char *str)
{
	char	*ptr;
	int		i;

	ptr = str;
	if (check_for_percentage(e, str))
		return (++ptr);
	while (*ptr)
	{
		i = 0;
		while (TYPES_PAT[i])
		{
			if (*ptr == TYPES_PAT[i])
			{
				if ((new_link(e, str, ptr, 1)) == -1)
					return (NULL);
				return (++ptr);
			}
			i++;
		}
		ptr++;
	}
	return (NULL);
}

int				read_str(t_printf_tools *e, char *str)
{
	char	*ptr;
	int		boo;
	char	*tmp;

	ptr = str;
	tmp = ptr;
	while (*ptr)
	{
		if (*ptr == '%' || *ptr == '^')
		{
			boo = 1;
			if ((int)(ptr - tmp))
				new_link(e, tmp, ptr, 0);
			tmp = ptr;
			if (*ptr == '%' && (ptr = parse_format(e, ++ptr)) == NULL)
				ptr = no_type(e, ++tmp);
			else if (*ptr == '^' && (ptr = get_color(e, ++ptr)) == NULL)
				ptr = no_type(e, tmp);
			tmp = ptr;
		}
		else
			*(++ptr) == '\0' ? boo = 0 : boo;
	}
	boo == 0 ? new_link(e, tmp, ptr, 0) : 0;
	return (0);
}
