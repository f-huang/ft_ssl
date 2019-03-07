/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 20:02:52 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/07 14:38:35 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <libft.h>
#include <message_digest/md5.h>

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

	if (!(options & OPTION_QUIET) && !(options & OPTION_REVERSE) && reader.name)
	{
		ft_putstr(reader.type == ARG_FILE ? (STRINGIFY(MD5)" (") : (STRINGIFY(MD5)" (\""));
		ft_putstr(reader.name);
		ft_putstr(reader.type == ARG_FILE ? ") = " : "\") = ");
	}
	if (reader.type == ARG_FILE && reader.content && options & OPTION_PRINT)
		ft_putstr(reader.content);
	i = 0;
	while (i < 4)
	{
		tmp = ft_utoa_hex(swap_32(words[i]));
		ft_putstr(tmp);
		ft_strdel(&tmp);
		++i;
	}
	if (!(options & OPTION_QUIET) && (options & OPTION_REVERSE) && reader.name)
	{
		if (!reader.name)
			ft_putstr(" \"\"");
		else
		{
			ft_putstr(" \"");
			ft_putstr(reader.name);
			ft_putstr("\"");
		}
	}
	write(1, "\n", 1);
	(void)options;
}

static void				exec_md5_algorithm(t_md5 *md5,
								const uint32_t *s,
								const uint32_t *k)
{
	uint32_t		chunks[16];
	uint32_t		j;
	uint32_t		words[N_WORDS];

	ft_bzero(&chunks, sizeof(uint32_t) * 16);
	j = 0;
	while (j < md5->n_chunks)
	{
		ft_memcpy(words, md5->words, N_WORDS * sizeof(uint32_t));
		ft_memcpy(chunks, md5->msg + j * 16, 64);
		md5_compress(s, k, chunks, words);
		md5->words[0] += words[0];
		md5->words[1] += words[1];
		md5->words[2] += words[2];
		md5->words[3] += words[3];
		// printf("Block=%d Proccessed: A=%u B=%u C=%u D=%u\n\n", j, md5->words[0], md5->words[1], md5->words[2], md5->words[3]);
		++j;
	}
}

void					md5_hash(t_reader reader, uint32_t options)
{
	t_md5			md5;
	const uint32_t	initial_words[] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};
	const uint32_t	*s;
	const uint32_t	*k;

	s = md5_get_shift_amounts();
	k = md5_get_sinus_constants();
	ft_bzero(&md5, sizeof(md5));
	ft_memcpy(md5.words, initial_words, N_WORDS * sizeof(uint32_t));
	md5.input_size_in_bits = BITS_IN_OCTET * sizeof(char) * reader.size;
	md5.n_chunks = ft_ceil(md5.input_size_in_bits + 65, CHUNK_SIZE_IN_BITS);
	// write(1, reader.content, reader.size);
	// printf("reader.size: %zu\ninput size in bit: %llu\n", reader.size, md5.input_size_in_bits);
	// printf("n_chunks: %u\n", md5.n_chunks);
	prepare_message(&md5, reader);
	exec_md5_algorithm(&md5, s, k);
	print_digest(reader, md5.words, options);
	ft_memdel((void**)&md5.msg);
	(void)options;
}
