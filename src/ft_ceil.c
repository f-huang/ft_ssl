/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceil.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 11:01:08 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/06 11:07:48 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

uint32_t			ft_ceil(uint32_t number, uint32_t base)
{
	if (number != 0 && number % base == 0)
		return (number);
	else
		return (((int)(number / base) + 1));
}
