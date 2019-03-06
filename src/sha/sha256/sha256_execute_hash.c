/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_execute_hash.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:26:53 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/06 16:44:39 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <libft.h>
#include <sha256.h>

#include <stdio.h>
static void		prepare_message(t_sha *sha, t_reader reader)
{
	const uint32_t	bits_per_int = BITS_IN_OCTET * sizeof(uint32_t);
	uint32_t		current_int;
	uint32_t		current_offset;

	sha->msg_size = N_WORDS_IN_CHUNK * sizeof(uint32_t) * sha->n_chunks;
	current_int = sha->input_size_in_bits / bits_per_int;
	current_offset = sha->input_size_in_bits % bits_per_int;
	// printf(" sizeof : %lu\n", sizeof(uint32_t));
	if (!(sha->msg = ft_memalloc(sha->msg_size)))
		return ;
	ft_memcpy(sha->msg, reader.content, reader.size);
	sha->msg[current_int] |= 0x80 << current_offset;
	sha->input_size_in_bits = swap_64(sha->input_size_in_bits);
	ft_memcpy(sha->msg + ((N_WORDS_IN_CHUNK * sha->n_chunks) - 2), (uint64_t*)&sha->input_size_in_bits, BITS_IN_OCTET);
	for (unsigned int i = 0; i < N_WORDS_IN_CHUNK * sha->n_chunks; i++)
		sha->msg[i] = swap_32(sha->msg[i]);

}

static void				print_digest(t_reader reader, uint32_t *words, int options)
{
	char			*tmp;
	int				i;

	if (reader.name)
	{
		ft_putstr(reader.type == ARG_FILE ? (STRINGIFY(SHA256)" (") : (STRINGIFY(SHA256)" (\""));
		ft_putstr(reader.name);
		ft_putstr(reader.type == ARG_FILE ? ") = " : "\") = ");
	}
	i = 0;
	while (i < 8)
	{
		// tmp = ft_utoa_hex(swap_32(words[i]));
		tmp = ft_utoa_hex(words[i]);
		ft_putstr(tmp);
		ft_strdel(&tmp);
		++i;
	}
	ft_putchar('\n');
	(void)options;
}

static uint32_t	sigma_lowercase(uint32_t value, unsigned int subscript)
{
	if (subscript == 0)
		return (right_rotate(value, 7) ^ right_rotate(value, 18) ^ (value >> 3));
	else if (subscript == 1)
		return (right_rotate(value, 17) ^ right_rotate(value, 19) ^ (value >> 10));
	return (0);
}

static uint32_t	sigma_uppercase(uint32_t value, unsigned int subscript)
{
	if (subscript == 0)
		return (right_rotate(value, 2) ^ right_rotate(value, 13) ^ right_rotate(value, 22));
	else if (subscript == 1)
		return (right_rotate(value, 6) ^ right_rotate(value, 11) ^ right_rotate(value, 25));
	return (0);
}

static uint32_t	ch(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ ((~x) & z));
}

static uint32_t	maj(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

static void				exec_sha256_algorithm(t_sha *sha,
								const uint32_t *k)
{
	uint32_t		words[64];
	uint32_t		tmp_words[N_WORDS];
	uint32_t		j;
	uint32_t		tmp1;
	uint32_t		tmp2;

	j = 0;
	ft_bzero(&words, sizeof(uint32_t) * 64);
	while (j < sha->n_chunks)
	{
		ft_memcpy(&words, sha->msg + j * 16, 16 * sizeof(uint32_t));
		ft_memcpy(&tmp_words, sha->words, N_WORDS * sizeof(uint32_t));
		for (int i = 16; i < 64; i++)
		{
			words[i] = sigma_lowercase(words[i - 15], 0)
					+ sigma_lowercase(words[i - 2], 1)
					+ words[i - 16] + words[i - 7];
		}

		// printf("[init] A=%x B=%x C=%x D=%x E=%x F=%x G=%x H=%x\n",
		// tmp_words[0], tmp_words[1], tmp_words[2], tmp_words[3], tmp_words[0], tmp_words[5], tmp_words[6], tmp_words[7]);
		for (int i = 0; i < 64; i++)
		{

			tmp1 = tmp_words[7] + sigma_uppercase(tmp_words[4], 1)
					+ ch(tmp_words[4], tmp_words[5], tmp_words[6])
					+ k[i] + words[i];
			tmp2 = sigma_uppercase(tmp_words[0], 0) + maj(tmp_words[0], tmp_words[1], tmp_words[2]);

			tmp_words[7] = tmp_words[6];
			tmp_words[6] = tmp_words[5];
			tmp_words[5] = tmp_words[4];
			tmp_words[4] = tmp_words[3] + tmp1;
			tmp_words[3] = tmp_words[2];
			tmp_words[2] = tmp_words[1];
			tmp_words[1] = tmp_words[0];
			tmp_words[0] = tmp1 + tmp2;
			// printf("[t=%2i] A=%x B=%x C=%x D=%x E=%x F=%x G=%x H=%x\n", i,
			// tmp_words[0], tmp_words[1], tmp_words[2], tmp_words[3], tmp_words[0], tmp_words[5], tmp_words[6], tmp_words[7]);
		}
		for (int i = 0; i < N_WORDS; i++)
		{
			// printf("H%i = %x + %x = %x\n", i, sha->words[i], tmp_words[i], sha->words[i] + tmp_words[i]);
			sha->words[i] += tmp_words[i];
		}
		++j;
	}
}

void			sha256_execute_hash(t_reader reader, int options)
{
	t_sha			sha;
	const uint32_t	initial_words[] = {
		0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A,
		0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19
	};
	const uint32_t	*k;

	ft_bzero(&sha, sizeof(t_sha));
	ft_memcpy(sha.words, initial_words, N_WORDS * sizeof(uint32_t));
	k = sha256_get_round_constants();
	sha.input_size_in_bits = BITS_IN_OCTET * sizeof(char) * reader.size;
	sha.n_chunks = ft_ceil(sha.input_size_in_bits +
						(((CHUNK_SIZE_IN_BITS - 64) -
						(sha.input_size_in_bits + 1))
						% CHUNK_SIZE_IN_BITS) + 65,
						CHUNK_SIZE_IN_BITS);
	// printf("reader.size: %zu\ninput size in bit: %llu\n", reader.size, md5.input_size_in_bits);
	prepare_message(&sha, reader);
	// for (uint32_t n_chunk = 0; n_chunk < sha.n_chunks; n_chunk++)
	// {
	// 	printf("Chunk %d\n", n_chunk);
	// 	for (uint32_t i = 0; i < 16; i++)
	// 	{
	// 		printf("(%2i) %#08x\n", i, sha.msg[n_chunk * 16 + i]);
	// 	}
	// }
	// printf("\n");
	// printf("padded message: %s", (char*)sha.msg);
	exec_sha256_algorithm(&sha, k);
	print_digest(reader, sha.words, options);
}
