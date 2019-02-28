/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intabndup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 11:11:38 by fhuang            #+#    #+#             */
/*   Updated: 2017/09/15 11:17:36 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

int		*ft_intabndup(int *tab_to_dup, size_t start, size_t end)
{
	size_t	i;
	size_t	size;
	int		*ret;

	size = end - start;
	if (!(ret = (int*)ft_memalloc(sizeof(int) * size)))
		return (NULL);
	i = 0;
	while (start < end)
	{
		ret[i] = tab_to_dup[start];
		i++;
		start++;
	}
	return (ret);
}
