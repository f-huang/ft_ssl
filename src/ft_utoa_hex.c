/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 20:08:22 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/01 20:23:54 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <libft.h>
#include <stdio.h>

#define UTOA_HEX_BASE 16
#define UTOA_LENGTH 8

char		*ft_utoa_hex(uint32_t n)
{
	char const	pattern[] = "0123456789abcdef";
	char		*ret;
	int			len;

	len = UTOA_LENGTH;
	if ((ret = ft_strnew(UTOA_LENGTH)) == NULL)
		return (NULL);
	while (--len >= 0)
	{
		ret[len] = pattern[n % UTOA_HEX_BASE];
		n /= UTOA_HEX_BASE;
	}
	return (ret);
}
