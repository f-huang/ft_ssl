/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:18:28 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/08 14:24:37 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# include <stdint.h>
# include <ft_ssl.h>
# include <message_digest/message_digest.h>

# define SHA_OPTIONS "pqrsv"

# define SHA_COMMAND "SHA512"

# define CHUNK_SIZE_IN_BITS 1024
# define WORD_SIZE_IN_BITS 64
# define N_WORDS_IN_CHUNK (CHUNK_SIZE_IN_BITS / WORD_SIZE_IN_BITS)

# define N_WORDS 8
# define N_ROUNDS 80


typedef struct	s_sha
{
	uint64_t	*msg;
	uint64_t	msg_size;
	uint32_t	n_chunks;
	unsigned char	input_size_in_bits[16];
	uint64_t	words[N_WORDS];
}				t_sha;


void			sha512_execute_hash(t_reader reader, uint32_t options);
const uint64_t	*sha512_get_round_constants(void);
void			sha512_compress(uint64_t *words,
						const uint64_t *k,
						const uint64_t *chunk);
#endif
