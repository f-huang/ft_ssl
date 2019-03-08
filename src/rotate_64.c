/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 11:21:03 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/08 13:21:26 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

uint64_t	left_rotate_64(uint64_t value, unsigned int count)
{
	return ((value << count) | (value >> (64 - count)));
}

uint64_t	right_rotate_64(uint64_t value, unsigned int count)
{
	return ((value >> count) | (value << (64 - count)));
}
