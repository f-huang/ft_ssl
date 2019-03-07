/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:26:53 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/07 14:50:17 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <libft.h>
#include <message_digest/sha256.h>

static void		prepare_message(t_sha *sha, t_reader reader)
{
	const uint32_t	bits_per_int = BITS_IN_OCTET * sizeof(uint32_t);
	uint32_t		current_int;
	uint32_t		current_offset;

	sha->msg_size = N_WORDS_IN_CHUNK * sizeof(uint32_t) * sha->n_chunks;
	current_int = sha->input_size_in_bits / bits_per_int;
	current_offset = sha->input_size_in_bits % bits_per_int;
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
		return (right_rotate(value, 7)
				^ right_rotate(value, 18)
				^ (value >> 3));
	else if (subscript == 1)
		return (right_rotate(value, 17)
				^ right_rotate(value, 19)
				^ (value >> 10));
	return (0);
}

static void				exec_sha256_algorithm(t_sha *sha,
								const uint32_t *k)
{
	uint32_t		chunk[64];
	uint32_t		tmp_words[N_WORDS];
	uint32_t		j;
	int				i;

	j = 0;
	ft_bzero(&chunk, sizeof(uint32_t) * 64);
	while (j < sha->n_chunks)
	{
		ft_memcpy(&chunk, sha->msg + j * 16, 16 * sizeof(uint32_t));
		ft_memcpy(&tmp_words, sha->words, N_WORDS * sizeof(uint32_t));
		i = 15;
		while (++i < 64)
			chunk[i] = sigma_lowercase(chunk[i - 15], 0)
					+ sigma_lowercase(chunk[i - 2], 1)
					+ chunk[i - 16] + chunk[i - 7];
		sha256_compress(tmp_words, k, chunk);
		i = -1;
		while (++i < N_WORDS)
			sha->words[i] += tmp_words[i];
		++j;
	}
}

void			sha256_hash(t_reader reader, uint32_t options)
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
	prepare_message(&sha, reader);
	exec_sha256_algorithm(&sha, k);
	print_digest(reader, sha.words, options);
}
