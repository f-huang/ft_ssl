/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_compress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 17:55:23 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/07 15:28:15 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <message_digest/sha256.h>

static uint32_t	sum_0(uint32_t value)
{
	return (right_rotate_32(value, 2)
				^ right_rotate_32(value, 13)
				^ right_rotate_32(value, 22));
}

static uint32_t	sum_1(uint32_t value)
{
	return (right_rotate_32(value, 6)
			^ right_rotate_32(value, 11)
			^ right_rotate_32(value, 25));
}

static uint32_t	ch(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ ((~x) & z));
}

static uint32_t	maj(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

void	sha256_compress(uint32_t *words,
						const uint32_t *k,
						const uint32_t *chunk)
{
	uint32_t	i;
	uint32_t		tmp1;
	uint32_t		tmp2;

	i = 0;
	while (i < N_ROUNDS)
	{
		tmp1 = words[7] + sum_1(words[4])
				+ ch(words[4], words[5], words[6])
				+ k[i] + chunk[i];
		tmp2 = sum_0(words[0]) + maj(words[0], words[1], words[2]);
		words[7] = words[6];
		words[6] = words[5];
		words[5] = words[4];
		words[4] = words[3] + tmp1;
		words[3] = words[2];
		words[2] = words[1];
		words[1] = words[0];
		words[0] = tmp1 + tmp2;
		++i;
	}
}
