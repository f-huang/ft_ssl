/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 11:21:03 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/08 13:15:23 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

uint32_t	left_rotate_32(uint32_t value, unsigned int count)
{
	return ((value << count) | (value >> (32 - count)));
}

uint32_t	right_rotate_32(uint32_t value, unsigned int count)
{
	return ((value >> count) | (value << (32 - count)));
}
