/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 13:40:41 by fhuang            #+#    #+#             */
/*   Updated: 2018/01/18 17:58:39 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_n(unsigned char n, int base)
{
	int					ret;

	ret = 1;
	while (n / base)
	{
		ret++;
		n /= base;
	}
	return (ret);
}

char		*ft_ctoa_base(char n, int base, int is_uin, int *is_neg)
{
	const char			pattern[] = HEX_NUMBERS;
	char				*ret;
	unsigned char		uin;
	int					len;
	int					neg;

	neg = (base == 10 && n < 0) ? 1 : 0;
	neg && is_uin == 0 ? ABS(n) : 1;
	uin = (unsigned char)n;
	len = count_n(uin, base);
	if ((ret = ft_strnew(len)) == NULL)
		return (NULL);
	ret[len--] = 0;
	while (len >= 0)
	{
		ret[len] = pattern[uin % base];
		uin /= base;
		len--;
	}
	*is_neg = is_uin == 0 ? neg : 0;
	return (ret);
}
