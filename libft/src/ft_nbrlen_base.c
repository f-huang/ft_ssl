/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 13:11:52 by fhuang            #+#    #+#             */
/*   Updated: 2017/10/19 18:32:56 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t		ft_nbrlen_base(unsigned long n, int base)
{
	size_t		size;

	size = 1;
	while (n / base)
	{
		n /= base;
		size++;
	}
	return (size);
}
