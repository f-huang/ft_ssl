/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 15:58:33 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/28 19:43:10 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdint.h>

# define SSL_ERROR_USAGE 1
# define SSL_ERROR_COMMAND_NOT_FOUND 2

# define NUMBER_OF_COMMANDS 4

# define STRINGIFY_MACRO_NAME(x) #x
# define STRINGIFY(x) STRINGIFY_MACRO_NAME(x)

enum			e_command_type
{
	MD5,
	SHA256,
	SHA512,
	WHIRLPOOL
};

# define USAGE_STRING "usage: ./ft_ssl command\n"

typedef struct	s_command
{
	char				*name;
	enum e_command_type	type;
	const char			*options;
	int					(*start)(char**, int*, uint8_t*);
}				t_command;

t_command		find_command(char *command);
const t_command	*get_commands(void);

#endif
