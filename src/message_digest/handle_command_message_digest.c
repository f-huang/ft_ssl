/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command_message_digest.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 13:48:51 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/07 14:40:38 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <libft.h>
#include <ft_ssl.h>
#include <message_digest/message_digest.h>

static int	handle_error(const char *command, int error, int c)
{
	if (error == ERROR_ILLEGAL_OPTION)
	{
		ft_putstr_fd("ft_ssl ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": illegal option -- ", 2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (error == ERROR_OPTION_REQUIRES_ARGUMENT)
	{
		ft_putstr_fd("ft_ssl ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": option requires an argument -- s\n", 2);
	}
	return (-1);
}

static void	exec_hash(const t_command_keeper command, char *str, uint32_t *options)
{
	t_reader	reader;

	ft_bzero(&reader, sizeof(t_reader));
	reader = (t_reader){
		.size = !str ? 0 : ft_strlen(str),
		.content = !str ? NULL : ft_strdup(str),
		.name = str,
		.type = ARG_STRING
	};
	command.hash(reader, *options);
}

static char	*handle_string_option(char **av, int *i, int j)
{
	char		*str;
	t_reader	reader;

	ft_bzero(&reader, sizeof(t_reader));
	str = NULL;
	if (!av[*i][j + 1] && !av[*i + 1])
		return (NULL);
	else if (av[*i][j + 1])
		str = av[*i] + j + 1;
	else
	{
		++(*i);
		str = av[*i];
	}
	return (str);
}

static int	parse_options(char **av,
						int *i,
						uint32_t *options,
						const t_command_keeper command_keeper)
{
	int		j;
	char	*tmp;
	int		error;
	t_reader	reader;

	j = 1;
	error = 0;
	ft_bzero(&reader, sizeof(t_reader));
	while (av[*i][j])
	{
		if (av[*i][j] == 's')
		{
			*options |= OPTION_STRING;
			if ((tmp = handle_string_option(av, i, j)) == NULL)
				return (handle_error(command_keeper.name, ERROR_OPTION_REQUIRES_ARGUMENT, 0));
			exec_hash(command_keeper, tmp, options);
			return (0);
		}
		else if (av[*i][j] == 'p')
		{
			if (*options & OPTION_PRINT)
				exec_hash(command_keeper, NULL, options);
			else
			{
				*options |= OPTION_PRINT;
				error = read_file(NULL, command_keeper.name, *options, command_keeper.hash);
			}
		}
		else if (av[*i][j] == 'r')
			*options |= OPTION_REVERSE;
		else if (av[*i][j] == 'q')
			*options |= OPTION_QUIET;
		else
			return (handle_error(command_keeper.name, ERROR_ILLEGAL_OPTION, av[*i][j]));
		++j;
	}
	return (error);
}

static int	start(char **av, int *i, uint32_t *options, const t_command_keeper command_keeper)
{
	int		error;

	error = 0;
	if (!(*options & STOP_READING_OPTIONS) && av[*i][0] == '-' && av[*i][1])
	{
		if ((error |= parse_options(av, i, options, command_keeper)) < 0)
			return (1);
		if (!av[*i + 1] && !(*options & OPTION_STRING) && ((*options & OPTION_QUIET) || (*options & OPTION_REVERSE)))
			exec_hash(command_keeper, NULL, options);
	}
	else
	{
		*options |= STOP_READING_OPTIONS;
		error |= read_file(av[*i], command_keeper.name, *options, command_keeper.hash);
	}
	return (error);
}

int		handle_command_message_digest(int ac,
								char **av,
								const t_command_keeper command_keeper)
{
	int				i;
	int				error;
	uint32_t		options;

	i = 0;
	options = 0;
	if (ac == 2)
		read_file(NULL, command_keeper.name, options, command_keeper.hash);
	else
	{
		i = 1;
		while (av[++i])
			if (ft_strequ("--", av[i]))
				options |= STOP_READING_OPTIONS;
			else
			{
				if ((error = start(av, &i, &options, command_keeper)) == -1)
					return (1);
			}
	}
	return (0);
}
