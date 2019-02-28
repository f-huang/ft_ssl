/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 01:07:33 by fhuang            #+#    #+#             */
/*   Updated: 2017/10/20 14:36:32 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define FOUND 1
#define NOT_FOUND 0

static void	add_color(t_printf_tools *e, int color_number)
{
	t_color		ref;

	if (color_number == T_RED)
		new_link(e, RED, &(RED[6]), 0);
	else if (color_number == T_BLUE)
		new_link(e, BLUE, &(BLUE[6]), 0);
	else if (color_number == T_GREEN)
		new_link(e, GREEN, &(GREEN[6]), 0);
	else if (color_number == T_YELLOW)
		new_link(e, YELLOW, &(YELLOW[6]), 0);
	else if (color_number == T_MAGENTA)
		new_link(e, MAGENTA, &(MAGENTA[6]), 0);
	else if (color_number == T_CYAN)
		new_link(e, CYAN, &(CYAN[6]), 0);
	else if (color_number == 6)
		new_link(e, COLOR_RESET, &(COLOR_RESET[5]), 0);
	(void)ref;
}

static int	is_color(t_printf_tools *e, char *str, char *stop)
{
	const char	*t[8] = {"RED",\
		"GREEN", "YELLOW", "BLUE", "MAGENTA", "CYAN", "EOC", NULL};
	int			i;

	i = 0;
	while (t[i])
	{
		if (ft_strncmp(str, t[i], (size_t)(stop - str)) == 0)
		{
			add_color(e, i);
			return (FOUND);
		}
		i++;
	}
	return (NOT_FOUND);
}

char		*get_color(t_printf_tools *e, char *str)
{
	char		*stop;

	stop = str;
	while (*stop)
	{
		if (*stop == '^')
		{
			if ((is_color(e, str, stop)) == FOUND)
				return (++stop);
			else
			{
				new_link(e, --str, ++stop, 0);
				return (stop);
			}
		}
		stop++;
	}
	return (NULL);
}
