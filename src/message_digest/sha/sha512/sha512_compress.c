/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_compress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 17:55:23 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/07 18:31:21 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <message_digest/sha512.h>

static uint64_t	sum_0(uint64_t value)
{
	return (right_rotate(value, 28)
				^ right_rotate(value, 34)
				^ right_rotate(value, 39));
}

static uint64_t	sum_1(uint64_t value)
{
	return (right_rotate(value, 14)
			^ right_rotate(value, 18)
			^ right_rotate(value, 41));
}

static uint64_t	ch(uint64_t x, uint64_t y, uint64_t z)
{
	return ((x & y) ^ ((~x) & z));
}

static uint64_t	maj(uint64_t x, uint64_t y, uint64_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}
#include <stdio.h>
void	sha512_compress(uint64_t *words,
						const uint64_t *k,
						const uint64_t *chunk)
{
	uint64_t	i;
	uint64_t		tmp1;
	uint64_t		tmp2;

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
		printf("t=%llu A=%llx B=%llx C=%llx D=%llx\n\tE=%llx F=%llx G=%llx H=%llx\n", i,
		words[0], words[1], words[2], words[3],
		words[4], words[5], words[6], words[7]
	);
		++i;
	}
}
