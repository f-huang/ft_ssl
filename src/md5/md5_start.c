/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:56:50 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/06 11:43:35 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <md5.h>
#include <ft_ssl.h>

static int	handle_string_option(char **av, int options, int *i, int j)
{
	char		*str;
	t_reader	reader;

	ft_bzero(&reader, sizeof(t_reader));
	str = NULL;
	if (!av[*i][j + 1] && !av[*i + 1])
	{
		ft_putendl_fd("ft_ssl "MD5_COMMAND": option requires an argument -- s",
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
	md5_execute_hash(reader, options);
	ft_memdel(&reader.content);
	return (1);
}

static int	parse_options(char **av,
						int *i,
						int *options,
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
			error = read_file(NULL, command_name, *options, md5_execute_hash);
		}
		else if (av[*i][j] == 'r')
			*options |= OPTION_REVERSE;
		else if (av[*i][j] == 'q')
			*options |= OPTION_QUIET;
		else
		{
			ft_putstr_fd("ft_ssl "MD5_COMMAND": illegal option -- ", 2);
			ft_putchar_fd(av[*i][j], 2);
			ft_putstr_fd("\n", 2);
			return (-1);
		}
		++j;
	}
	return (error);
}

int			md5_start(char **av,
						int *i,
						uint8_t *stop_option,
						const char *command_name)
{
	int		options;
	int		error;

	options = 0;
	error = 0;
	if (*i == 0)
		error |= read_file(NULL, command_name, options, md5_execute_hash);
	else
	{
		if (!*stop_option && av[*i][0] == '-' && av[*i][1])
		{
			if ((error |= parse_options(av, i, &options, command_name)) == -1)
				return (1);
		}
		else
		{
			*stop_option = 1;
			error |= read_file(av[*i], command_name, options, md5_execute_hash);
		}
	}
	return (error);
}
