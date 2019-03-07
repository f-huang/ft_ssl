/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 15:58:33 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/07 14:37:49 by fhuang           ###   ########.fr       */
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

enum			e_command
{
	MD5,
	SHA256,
	SHA512,
	WHIRLPOOL
};

enum			e_command_type
{
	STANDARD,
	MESSAGE_DIGEST,
	CIPHER
};

enum			e_arg_type
{
	ARG_FILE,
	ARG_STRING
};

# define USAGE_STRING "usage: ./ft_ssl command\n"

typedef struct	s_reader
{
	void				*content;
	const char			*name;
	size_t				size;
	enum e_arg_type		type;
}				t_reader;

typedef struct	s_command_keeper
{
	enum e_command_type	type;
	enum e_command		command;
	const char			*name;
	int					(*handle_command)(int, char**, const struct s_command_keeper);
	void				(*hash)(t_reader, uint32_t);
}				t_command_keeper;

t_command_keeper		find_command(char *command);
const t_command_keeper	*get_commands(void);

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

int				handle_command_message_digest(int ac, char **av,
								const t_command_keeper command_keeper);
void			md5_hash(t_reader reader, uint32_t options);
void			sha256_hash(t_reader reader, uint32_t options);

#endif
