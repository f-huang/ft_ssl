/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:18:28 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/06 13:50:10 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# include <stdint.h>
# include <ft_ssl.h>

# define SHA_OPTIONS "pqrsv"

# define SHA_COMMAND "SHA256"

# define OPTION_PRINT (1 << 0)
# define OPTION_QUIET (1 << 1)
# define OPTION_REVERSE (1 << 2)
# define OPTION_VERBOSE (1 << 3)

# define CHUNK_SIZE_IN_BITS 512
# define WORD_SIZE_IN_BITS 32
# define N_WORDS_IN_CHUNK (CHUNK_SIZE_IN_BITS / WORD_SIZE_IN_BITS)

# define N_WORDS 8

typedef struct	s_sha
{
	uint32_t	*msg;
	uint32_t	msg_size;
	uint32_t	n_chunks;
	uint64_t	input_size_in_bits;
	uint32_t	words[N_WORDS];
}				t_sha;


void			sha256_execute_hash(t_reader reader, int options);
const uint32_t	*sha256_get_round_constants(void);

#endif
