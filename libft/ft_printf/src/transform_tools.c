/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 16:57:27 by fhuang            #+#    #+#             */
/*   Updated: 2017/10/19 11:49:43 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

void		push_char_front(t_print *link, char *str, char c, int n)
{
	char	*tmp;
	int		i;

	if (n < 0)
		return ;
	LEN += n;
	tmp = NULL;
	if ((tmp = ft_strdup(str)) == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < n)
		str[i++] = c;
	str[i] = 0;
	ft_strcat(str, tmp);
	if (tmp != NULL)
		ft_strdel(&tmp);
}

void		push_char_back(t_print *link, char *str, char c, int n)
{
	int		i;

	if (n < 0)
		return ;
	LEN += n;
	i = ft_strlen(str);
	while (n > 0)
	{
		str[i++] = c;
		n--;
	}
}
