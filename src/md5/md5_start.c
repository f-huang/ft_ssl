/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:56:50 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/28 20:09:23 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <md5.h>
#include <ft_ssl.h>

static int	handle_option_string(char **av, int options, int *i, int j)
{
	if (!av[*i][j + 1] && (!av[*i + 1] || (av[*i + 1] && !av[*i + 1][0])))
	{
		ft_printf_fd(2, "./ft_ssl: %s option requires an argument -- s\n", COMMAND_NAME);
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
	int			j;

	j = 1;
	while (av[*i][j])
	{
		if (av[*i][j] == 's')
		{
			if (handle_option_string(av, *options, i, j) == -1)
				return (-1);
			else
				break ;
		}
		else if (av[*i][j] == 'p')
			;
			// handle_stdin();
		else if (av[*i][j] == 'r')
			*options |= OPTION_REVERSE;
		else if (av[*i][j] == 'q')
			*options |= OPTION_QUIET;
		else
		{
			ft_printf_fd(2, "./ft_ssl: illegal option -- %c\n", av[*i][j]);
			return (-1);
		}
		++j;
	}
	return (0);
}

int		md5_start(char **av, int *i, uint8_t *stop_option)
{
	int		options;

	options = 0;
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
			ft_putstr("handle file : ");
			ft_putendl(av[*i]);
		}
	}
	return (0);
}
