/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:52:36 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/05 18:04:59 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include <stdint.h>
# include <ft_ssl.h>
/*
**	OPTIONS
**	-s string
**			Print a checksum of the given string.
**
**	-p      Echo stdin to stdout and append the checksum to stdout.
**
**	-q      Quiet mode - only the checksum is printed out.  Overrides the -r
**			option.
**
**	-r      Reverses the format of the output.  This helps with visual diffs.
**			Does nothing when combined with the -ptx options.
*/

# define MD5_OPTIONS "pqrsv"

# define MD5_COMMAND "md5"

# define OPTION_PRINT (1 << 0)
# define OPTION_QUIET (1 << 1)
# define OPTION_REVERSE (1 << 2)
# define OPTION_VERBOSE (1 << 3)

# define CHUNK_SIZE_IN_BITS 512
# define WORD_SIZE_IN_BITS 32
# define N_WORDS_IN_CHUNK (CHUNK_SIZE_IN_BITS / WORD_SIZE_IN_BITS)

# define N_WORDS 4

typedef struct	s_md5_round
{
	uint32_t	f;
	uint32_t	g;
}				t_md5_round;

typedef struct	s_md5
{
	uint32_t	*msg;
	uint32_t	msg_size;
	uint32_t	n_chunks;
	uint64_t	input_size_in_bits;
	uint32_t	words[N_WORDS];
}				t_md5;

int				md5_start(char **av,
							int *i,
							uint8_t *stop_option,
							const char *command_name);
void			md5_execute_hash(t_reader reader, int options);
void			md5_do_rounds(const uint32_t *s,
								const uint32_t *k,
								const uint32_t *chunks,
								uint32_t words[N_WORDS]);

const uint32_t	*md5_get_shift_amounts(void);
const uint32_t	*md5_get_sinus_constants(void);

#endif
