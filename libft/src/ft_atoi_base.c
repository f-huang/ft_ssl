/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 10:53:44 by fhuang            #+#    #+#             */
/*   Updated: 2016/09/02 14:04:30 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi_base(const char *str, int base)
{
	int			i;
	int			res;
	const char	*ptr;
	int			negatif;

	i = 0;
	res = 0;
	negatif = 1;
	ptr = str;
	while (*ptr && ft_isspace(*ptr))
		ptr++;
	negatif = *ptr == '-' ? -1 : 1;
	if (*ptr == '-' || *ptr == '+')
		ptr++;
	while (*ptr && ft_isdigit(*ptr))
	{
		res *= base;
		res += negatif * (*ptr - '0');
		ptr++;
	}
	return (res);
}
