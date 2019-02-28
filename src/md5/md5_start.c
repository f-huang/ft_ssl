/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:56:50 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/28 20:42:02 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <md5.h>
#include <ft_ssl.h>

static int	handle_option_string(char **av, int options, int *i, int j)
{
	if (!av[*i][j + 1] && (!av[*i + 1] || (av[*i + 1] && !av[*i + 1][0])))
	{
		ft_putendl_fd("ft_ssl "COMMAND_NAME": option requires an argument -- s",
		2);
		return (-1);
	}
	else if (av[*i][j + 1])
	{
		md5_execute_hash(av[*i] + j + 1, options);
		return (1);
	}
	else
	{
		++(*i);
		md5_execute_hash(av[*i], options);
		return (1);
	}
}

static int	parse_option(char **av, int *i, int *options)
{
	int		j;

	j = 1;
	while (av[*i][j])
	{
		if (av[*i][j] == 's')
			return (handle_option_string(av, *options, i, j) == -1 ? -1 : 0);
		else if (av[*i][j] == 'p')
			;
			// handle_stdin();
		else if (av[*i][j] == 'r')
			*options |= OPTION_REVERSE;
		else if (av[*i][j] == 'q')
			*options |= OPTION_QUIET;
		else
		{
			ft_printf_fd(2, "ft_ssl "COMMAND_NAME": illegal option -- %c\n",
			av[*i][j]);
			return (-1);
		}
		++j;
	}
	return (0);
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
		;
	else
	{
		if (!*stop_option && av[*i][0] == '-' && av[*i][1])
		{
			if (parse_option(av, i, &options) == -1)
				return (1);
		}
		else
		{
			*stop_option = 1;
			error = read_file(av[*i], command_name, options, md5_execute_hash);
		}
	}
	return (error);
}
