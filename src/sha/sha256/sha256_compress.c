/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_compress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 17:55:23 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/06 18:07:53 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

static uint32_t	sigma_uppercase_0(uint32_t value)
{
	return (right_rotate(value, 2)
				^ right_rotate(value, 13)
				^ right_rotate(value, 22));
}

static uint32_t	sigma_uppercase_1(uint32_t value)
{
	return (right_rotate(value, 6)
			^ right_rotate(value, 11)
			^ right_rotate(value, 25));
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
	while (i < 64)
	{
		tmp1 = words[7] + sigma_uppercase_1(words[4])
				+ ch(words[4], words[5], words[6])
				+ k[i] + chunk[i];
		tmp2 = sigma_uppercase_0(words[0]) + maj(words[0], words[1], words[2]);
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