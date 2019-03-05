/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_do_rounds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:06:23 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/05 17:48:54 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <md5.h>

static t_md5_round	F(uint32_t *words, uint32_t i)
{
	return (t_md5_round){
		.f = (words[1] & words[2]) | ((~words[1]) & words[3]),
		.g = i
	};
}


static t_md5_round	G(uint32_t *words, uint32_t i)
{
	return (t_md5_round){
		.f = (words[3] & words[1]) | ((~words[3]) & words[2]),
		.g = (5 * i + 1) % 16
	};
}

static t_md5_round	H(uint32_t *words, uint32_t i)
{
	return (t_md5_round){
		.f = words[1] ^ words[2] ^ words[3],
		.g = (3 * i + 5) % 16
	};
}

static t_md5_round	I(uint32_t *words, uint32_t i)
{
	return (t_md5_round){
		.f = words[2] ^ (words[1] | (~words[3])),
		.g = (7 * i) % 16
	};
}
#include <stdio.h>
void			md5_do_rounds(const uint32_t *s,
							const uint32_t *k,
							const uint32_t *chunks,
							uint32_t words[N_WORDS])
{
	int				i;
	t_md5_round		round;

	i = 0;
	while (i < 64)
	{
		// printf("[%d] A=%u B=%u C=%u D=%u\n", i, words[0], words[1], words[2], words[3]);
		if (i >= 0 && i < 16)
			round = F(words, i);
		else if (i > 15 && i < 32)
			round = G(words, i);
		else if (i > 31 && i < 48)
			round = H(words, i);
		else
			round = I(words, i);
		round.f = round.f + words[0] + k[i] + chunks[round.g];
		words[0] = words[3];
		words[3] = words[2];
		words[2] = words[1];
		words[1] = words[1] + ((round.f << s[i]) | (round.f >> (32 - s[i])));
		++i;
	}
}
