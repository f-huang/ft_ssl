/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:56:50 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/28 19:50:26 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <md5.h>
#include <ft_ssl.h>

static int	parse_option(char **av, int *i)
{
	int			j;
	int			options;

	j = 1;
	options = 0;
	while (av[*i][j])
	{
		if (av[*i][j] == 's')
		{
			if (!av[*i][j + 1] && (!av[*i + 1] || (av[*i + 1] && !av[*i + 1][0])))
			{
				ft_printf_fd(2, "./ft_ssl: %s option requires an argument -- s\n", COMMAND_NAME);
				return (-1);
			}
			else if (av[*i][j + 1])
				break; //use end of string as arg
			else
			{
				++(*i);
				break; //
			}
		}
		else if (av[*i][j] == 'p')
			;
			// handle_stdin();
		else if (av[*i][j] == 'r')
			options |= OPTION_REVERSE;
		else if (av[*i][j] == 'q')
			options |= OPTION_QUIET;
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
	if (*i == 0)
		;
	else
	{
		if (!*stop_option && av[*i][0] == '-' && av[*i][1])
		{
			if (parse_option(av, i) == -1)
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
