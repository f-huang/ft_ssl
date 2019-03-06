/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 15:58:33 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/06 19:51:58 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdint.h>
# include <stddef.h>

# define SSL_ERROR_USAGE 1
# define SSL_ERROR_COMMAND_NOT_FOUND 2

# define STRINGIFY_MACRO_NAME(x) #x
# define STRINGIFY(x) STRINGIFY_MACRO_NAME(x)

# define BITS_IN_OCTET 8
# define STOP_READING_OPTIONS (1 << 31)

enum			e_command_type
{
	MD5,
	SHA256,
	SHA512,
	WHIRLPOOL
};

enum			e_arg_type
{
	ARG_FILE,
	ARG_STRING
};

# define USAGE_STRING "usage: ./ft_ssl command\n"

typedef struct	s_command
{
	const char			*name;
	enum e_command_type	type;
	int					(*start)(char**, int*, uint32_t*, const char*);
}				t_command;

typedef struct	s_reader
{
	void				*content;
	const char			*name;
	size_t				size;
	enum e_arg_type		type;
}				t_reader;

t_command		find_command(char *command);
const t_command	*get_commands(void);

int				read_file(const char *path,
							const char *command,
							uint32_t options,
							void (*hash)(t_reader, uint32_t));

uint32_t		left_rotate(uint32_t value, unsigned int count);
uint32_t		right_rotate(uint32_t value, unsigned int count);

char			*ft_utoa_hex(uint32_t n);
uint32_t		swap_32(uint32_t value);
uint64_t		swap_64(uint64_t value);
uint32_t		ft_ceil(uint32_t number, uint32_t base);

int				md5_start(char **av,
							int *i,
							uint32_t *options,
							const char *command_name);
int				sha256_start(char **av,
						int *i,
						uint32_t *options,
						const char *command_name);

#endif
