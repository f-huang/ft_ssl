/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:26:53 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/08 16:06:35 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <libft.h>
#include <message_digest/sha512.h>

#include <stdio.h>

static void		swap_bits(unsigned char input_size_in_bits[16])
{
	int		i;
	unsigned char	tmp;

	i = 0;
	while (i < 8)
	{
		tmp = input_size_in_bits[i];
		input_size_in_bits[i] = input_size_in_bits[15 - i];
		input_size_in_bits[15 - i] = tmp;
		++i;
	}
}


static void		prepare_message(t_sha *sha, t_reader reader)
{
	const uint64_t	bits_per_int = BITS_IN_OCTET * sizeof(uint64_t);
	uint64_t		current_int;
	uint64_t		current_offset;

	sha->msg_size = N_WORDS_IN_CHUNK * sizeof(uint64_t) * sha->n_chunks;
	current_int = *(uint64_t*)sha->input_size_in_bits / bits_per_int;
	current_offset = *(uint64_t*)sha->input_size_in_bits % bits_per_int;
	if (!(sha->msg = ft_memalloc(sha->msg_size)))
		return ;
	printf("message size: %llu bytes\n", sha->msg_size);
	ft_memcpy(sha->msg, reader.content, reader.size);
	for (uint64_t i = 0; i < sha->msg_size; i++)
	{
		unsigned char c = ((char*)sha->msg)[i] ;
		printf ("%02x ", c) ;
	}
	printf("\n::NOW::\n");
	sha->msg[current_int] |= (uint32_t)(0x80 << current_offset);
	swap_bits(sha->input_size_in_bits);
	ft_memcpy(sha->msg + ((N_WORDS_IN_CHUNK * sha->n_chunks) - 2), sha->input_size_in_bits, 16);
	for (unsigned int i = 0; i < N_WORDS_IN_CHUNK * sha->n_chunks; i++)
		sha->msg[i] = swap_64(sha->msg[i]);

	for (uint32_t n_chunk = 0; n_chunk < sha->n_chunks; n_chunk++)
	{
		printf("Chunk %u\n", n_chunk);
		for (uint32_t i = 0; i < N_WORDS_IN_CHUNK; i++)
		{
			printf("(%i) %llu\n", i, sha->msg[n_chunk * 16 + i]);
		}
	}
	printf("\n");
	printf("padded message: %s", (char*)sha->msg);

}

static void				print_digest(t_reader reader, uint64_t *words, int options)
{
	char			*tmp;
	int				i;

	if (reader.name)
	{
		ft_putstr(reader.type == ARG_FILE ? (STRINGIFY(SHA512)" (") : (STRINGIFY(SHA512)" (\""));
		ft_putstr(reader.name);
		ft_putstr(reader.type == ARG_FILE ? ") = " : "\") = ");
	}
	i = 0;
	while (i < N_WORDS)
	{
		tmp = ft_utoa_hex_64(words[i]);
		ft_putstr(tmp);
		ft_strdel(&tmp);
		++i;
	}
	ft_putchar('\n');
	(void)options;
}

static uint64_t	sigma(uint64_t value, unsigned int subscript)
{
	if (subscript == 0)
		return (right_rotate_64(value, 1)
				^ right_rotate_64(value, 8)
				^ (value >> 7));
	else if (subscript == 1)
		return (right_rotate_64(value, 19)
				^ right_rotate_64(value, 61)
				^ (value >> 6));
	return (0);
}

static void				exec_sha512_algorithm(t_sha *sha,
								const uint64_t *k)
{
	uint64_t		chunk[N_ROUNDS];
	uint64_t		tmp_words[N_WORDS];
	uint32_t		j;
	int				i;

	j = 0;

	ft_bzero(&chunk, sizeof(uint64_t) * N_ROUNDS);
	while (j < sha->n_chunks)
	{
		ft_memcpy(&chunk, sha->msg + j * 16, 16 * sizeof(uint64_t));
		ft_memcpy(&tmp_words, sha->words, N_WORDS * sizeof(uint64_t));
		printf("\n");
		i = 15;
		while (++i < N_ROUNDS)
			chunk[i] = sigma(chunk[i - 15], 0)
					+ sigma(chunk[i - 2], 1)
					+ chunk[i - 16] + chunk[i - 7];
		// for (int i = 0; i < N_ROUNDS; i++)
		// 	printf("%llx\n", chunk[i]);
		printf("\ninit A=%llx B=%llx C=%llx D=%llx\n\tE=%llx F=%llx G=%llx H=%llx\n",
		tmp_words[0], tmp_words[1], tmp_words[2], tmp_words[3],
		tmp_words[4], tmp_words[5], tmp_words[6], tmp_words[7]);
		sha512_compress(tmp_words, k, chunk);
		i = -1;
		while (++i < N_WORDS)
			sha->words[i] += tmp_words[i];
		++j;
	}
}

char 	*convert(uint64_t toto)
{
	uint64_t *ret;
	ret = &toto;
	return ((char*)ret);
}

void			sha512_hash(t_reader reader, uint32_t options)
{
	t_sha			sha;
	const uint64_t	initial_words[] = {
		0x6A09E667F3BCC908, 0xBB67AE8584CAA73B,
		0x3C6EF372FE94F82B, 0xA54FF53A5F1D36F1,
		0x510E527FADE682D1, 0x9B05688C2B3E6C1F,
		0x1F83D9ABFB41BD6B, 0x5BE0CD19137E2179
	};
	const uint64_t	*k;

	(void)options;
	ft_bzero(&sha, sizeof(t_sha));
	ft_memcpy(sha.words, initial_words, N_WORDS * sizeof(uint64_t));
	k = sha512_get_round_constants();
	ft_memcpy(sha.input_size_in_bits, &(BITS_IN_OCTET * sizeof(char) * reader.size), 16);
	printf("%lu\n", BITS_IN_OCTET * sizeof(char) * reader.size);
	printf("%llu\n", *(uint64_t*)(convert(BITS_IN_OCTET * sizeof(char) * reader.size)));
	for (int i = 0; i < 16; i++)
	{
		unsigned char c = ((char*)sha.input_size_in_bits)[i] ;
		printf ("%02x ", c) ;
		// printf ("%s ", test(c)) ;
	}
	printf("\n");

	sha.n_chunks = ft_ceil(*(uint64_t*)sha.input_size_in_bits +
						(((CHUNK_SIZE_IN_BITS - 128) -
						(*(uint64_t*)sha.input_size_in_bits + 1))
						% CHUNK_SIZE_IN_BITS) + 129,
						CHUNK_SIZE_IN_BITS);
	prepare_message(&sha, reader);
	exec_sha512_algorithm(&sha, k);
	print_digest(reader, sha.words, options);
}
