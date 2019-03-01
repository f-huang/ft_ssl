/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_execute_hash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 20:02:52 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/01 19:57:27 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <libft.h>
#include <md5.h>

static uint32_t	swap_32(uint32_t value)
{
	return ((value >> 24) |
		((value & 0xFF0000) >> 8) |
		((value & 0xFF00) << 8) |
		(value << 24));
}

static uint32_t	get_closest_multiple(uint32_t number)
{
	if (number != 0 && number % CHUNK_SIZE_IN_BITS == 0)
		return (number);
	else
		return (((int)(number / CHUNK_SIZE_IN_BITS) + 1));
}

static void	prepare_message(t_md5 *md5, t_reader reader)
{
	const uint32_t	bits_per_int = 8 * sizeof(uint32_t);
	uint32_t		current_int;
	uint32_t		current_offset;
	uint64_t		swap;

	md5->msg_size = 16 * sizeof(uint32_t) * md5->n_chunks;
	current_int = md5->input_size_in_bits / bits_per_int;
	current_offset = md5->input_size_in_bits % bits_per_int;
	if (!(md5->msg = ft_memalloc(md5->msg_size)))
		return ;
	ft_memcpy(md5->msg, reader.content, reader.size);
	md5->msg[current_int] |= 0x80 << current_offset;
	// printf("\nreader { .size: %zu } message { .size: %u }\n", reader.size, md5->msg_size);
	// printf("bef. | msg[index]: %u\n", md5->msg[current_int]);
	swap = md5->input_size_in_bits;
	ft_memcpy(md5->msg + ((16 * md5->n_chunks) - 2), &swap, 8);

	printf("\n");
	for (int i = 0; i < 16; i++)
	{
		printf("(%i) %#x\n", i, md5->msg[i]);
	}
	printf("\n");
	// printf("af.  | msg[index]: %u\n", md5->msg[current_int]);
	// printf("Input length (in bits): %llu\nFinal message length (in bytes): %u\n", md5->input_size_in_bits, md5->msg_size);
	printf("Int: %u\nOffset: %u\n", current_int, current_offset);
	printf("padded message: %s", (char*)md5->msg);
}

static const uint32_t	*break_into_chunks(uint32_t *msg)
{
	static uint32_t		chunks[16];

	ft_bzero(&chunks, sizeof(uint32_t) * 16);
	ft_memcpy(chunks, msg, 64);
	return (chunks);
}

static void	print_digest(uint32_t *words)
{
	char			digest[16];

	ft_bzero(&digest, sizeof(char) * 16);
	printf("\n%x", swap_32(words[0]));
	printf("%x", swap_32(words[1]));
	printf("%x", swap_32(words[2]));
	printf("%x\n", swap_32(words[3]));
}

static void	exec_md5_algorithm(t_md5 md5)
{
	uint32_t		final_words[] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};
	uint32_t		words[4];
	const uint32_t	*s;
	const uint32_t	*k;
	uint32_t		j;
	uint32_t		i;
	uint32_t		g;
	uint32_t		f;
	const uint32_t		*chunks;

	s = md5_get_shift_amounts();
	k = md5_get_sinus_constants();
	j = 0;
	while (j < md5.n_chunks)
	{
		ft_memcpy(words, final_words, 4 * sizeof(uint32_t));
		chunks = break_into_chunks(md5.msg);
		i = 0;
		while (i < 64)
		{
			if (i == 0 || (i > 0 && i < 16))
			{
				f = (words[1] & words[2]) | ((~words[1]) & words[3]);
				g = i;
			}
			else if (i > 15 && i < 32)
			{
				f = (words[3] & words[1]) | ((~words[3]) & words[2]);
				g = (5 * i + 1) % 16;
			}
			else if (i > 31 && i < 48)
			{
				f = words[1] ^ words[2] ^ words[3];
				g = (3 * i + 5) % 16;
			}
			else
			{
				f = words[2] ^ (words[1] | (~words[3]));
				g = (7 * i) % 16;
			}
			f = f + words[0] + k[i] + chunks[g];
			words[0] = words[3];
			words[3] = words[2];
			words[2] = words[1];
			words[1] = words[1] + ((f << s[i]) | (f >> (32 - s[i])));
			++i;
		}
		final_words[0] += words[0];
		final_words[1] += words[1];
		final_words[2] += words[2];
		final_words[3] += words[3];
		++j;
	}
	print_digest(final_words);
}

void		md5_execute_hash(t_reader reader, int options)
{
	t_md5		md5;

	ft_bzero(&md5, sizeof(md5));
	write(1, reader.content, reader.size);
	md5.input_size_in_bits = 8 * sizeof(char) * reader.size;
	md5.n_chunks = get_closest_multiple(md5.input_size_in_bits);
	// printf("\n--------------\nMD5-ing\n%s%c", input, input[len - 1] == '\n' ? '\0' : '\n');
	prepare_message(&md5, reader);
	// 	return ;
	// printf("%p\n", md5.msg);
	exec_md5_algorithm(md5);
	// ft_memdel(&md5.msg);
	(void)options;
}
