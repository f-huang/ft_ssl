/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:18:18 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/06 19:53:46 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <libft.h>
#include <sha256.h>

static int	handle_string_option(char **av, uint32_t options, int *i, int j)
{
	char		*str;
	t_reader	reader;

	ft_bzero(&reader, sizeof(t_reader));
	str = NULL;
	if (!av[*i][j + 1] && !av[*i + 1])
	{
		ft_putendl_fd("ft_ssl "SHA_COMMAND": option requires an argument -- s",
		2);
		return (-1);
	}
	else if (av[*i][j + 1])
		str = av[*i] + j + 1;
	else
	{
		++(*i);
		str = av[*i];
	}
	if (!str)
		return (0);
	reader = (t_reader){
		.size = ft_strlen(str),
		.content = ft_strdup(str),
		.name = str,
		.type = ARG_STRING
	};
	sha256_execute_hash(reader, options);
	ft_memdel(&reader.content);
	return (1);
}

static int	parse_options(char **av,
						int *i,
						uint32_t *options,
						const char *command_name)
{
	int		j;
	int		error;

	j = 1;
	error = 0;
	while (av[*i][j])
	{
		if (av[*i][j] == 's')
			return (handle_string_option(av, *options, i, j) == -1 ? -1 : 0);
		else if (av[*i][j] == 'p')
		{
			*options |= OPTION_PRINT;
			error = read_file(NULL, command_name, *options, sha256_execute_hash);
		}
		else if (av[*i][j] == 'r')
			*options |= OPTION_REVERSE;
		else if (av[*i][j] == 'q')
			*options |= OPTION_QUIET;
		else
		{
			ft_putstr_fd("ft_ssl "SHA_COMMAND": illegal option -- ", 2);
			ft_putchar_fd(av[*i][j], 2);
			ft_putstr_fd("\n", 2);
			return (-1);
		}
		++j;
	}
	return (error);
}

int			sha256_start(char **av,
						int *i,
						uint32_t *options,
						const char *command_name)
{
	int		error;

	error = 0;
	if (*i == 0)
		error |= read_file(NULL, command_name, *options, sha256_execute_hash);
	else
	{
		if (!(*options & STOP_READING_OPTIONS) && av[*i][0] == '-' && av[*i][1])
		{
			if ((error |= parse_options(av, i, options, command_name)) == -1)
				return (1);
		}
		else
		{
			*options |= STOP_READING_OPTIONS;
			error |= read_file(av[*i], command_name, *options, sha256_execute_hash);
		}
	}
	return (error);
}
