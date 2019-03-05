/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_execute_hash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 20:02:52 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/05 17:50:14 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <libft.h>
#include <md5.h>

static uint32_t			get_closest_multiple(uint32_t number)
{
	if (number != 0 && number % CHUNK_SIZE_IN_BITS == 0)
		return (number);
	else
		return (((int)(number / CHUNK_SIZE_IN_BITS) + 1));
}

static void				prepare_message(t_md5 *md5, t_reader reader)
{
	const uint32_t	bits_per_int = BITS_IN_OCTET * sizeof(uint32_t);
	uint32_t		current_int;
	uint32_t		current_offset;

	md5->msg_size = N_WORDS_IN_CHUNK * sizeof(uint32_t) * md5->n_chunks;
	current_int = md5->input_size_in_bits / bits_per_int;
	current_offset = md5->input_size_in_bits % bits_per_int;
	// printf(" sizeof : %lu\n", sizeof(uint32_t));
	// printf("message size: %u bytes\n", md5->msg_size);
	if (!(md5->msg = ft_memalloc(md5->msg_size)))
		return ;
	ft_memcpy(md5->msg, reader.content, reader.size);
	md5->msg[current_int] |= 0x80 << current_offset;
	ft_memcpy(md5->msg + ((N_WORDS_IN_CHUNK * md5->n_chunks) - 2), &md5->input_size_in_bits, BITS_IN_OCTET);
	// for (uint32_t n_chunk = 0; n_chunk < md5->n_chunks; n_chunk++)
	// {
	// 	printf("Chunk %d\n", n_chunk);
	// 	for (uint32_t i = 0; i < 16; i++)
	// 	{
	// 		printf("(%i) %u\n", i, md5 ->msg[n_chunk * 16 + i]);
	// 	}
	// }
	// printf("\n");
	// printf("padded message: %s", (char*)md5->msg);
}

static void				print_digest(t_reader reader, uint32_t *words, int options)
{
	char			*tmp;
	int				i;

	if (reader.name)
	{
		ft_putstr(reader.type == ARG_FILE ? (STRINGIFY(MD5)" (") : (STRINGIFY(MD5)" (\""));
		ft_putstr(reader.name);
		ft_putstr(reader.type == ARG_FILE ? ") = " : "\") = ");
	}
	i = 0;
	while (i < 4)
	{
		tmp = ft_utoa_hex(swap_32(words[i]));
		ft_putstr(tmp);
		ft_strdel(&tmp);
		++i;
	}
	write(1, "\n", 1);
	(void)options;
}

static void				exec_md5_algorithm(t_md5 *md5,
								const uint32_t *s,
								const uint32_t *k,
								const uint32_t *initial_words)
{
	uint32_t		chunks[16];
	uint32_t		j;
	uint32_t		words[N_WORDS];

	ft_bzero(&chunks, sizeof(uint32_t) * 16);
	ft_memcpy(md5->words, initial_words, N_WORDS * sizeof(uint32_t));
	j = 0;
	while (j < md5->n_chunks)
	{
		ft_memcpy(words, md5->words, N_WORDS * sizeof(uint32_t));
		ft_memcpy(chunks, md5->msg + j * 16, 64);
		md5_do_rounds(s, k, chunks, words);
		md5->words[0] += words[0];
		md5->words[1] += words[1];
		md5->words[2] += words[2];
		md5->words[3] += words[3];
		// printf("Block=%d Proccessed: A=%u B=%u C=%u D=%u\n\n", j, md5->words[0], md5->words[1], md5->words[2], md5->words[3]);
		++j;
	}
}

void					md5_execute_hash(t_reader reader, int options)
{
	t_md5			md5;
	const uint32_t	initial_words[] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};
	const uint32_t	*s;
	const uint32_t	*k;

	s = md5_get_shift_amounts();
	k = md5_get_sinus_constants();
	ft_bzero(&md5, sizeof(md5));
	write(1, reader.content, reader.size);
	md5.input_size_in_bits = BITS_IN_OCTET * sizeof(char) * reader.size;
	// printf("input size in bit: %llu\n", md5.input_size_in_bits);
	md5.n_chunks = get_closest_multiple(md5.input_size_in_bits);
	prepare_message(&md5, reader);
	exec_md5_algorithm(&md5, s, k, initial_words);
	print_digest(reader, md5.words, options);
}
