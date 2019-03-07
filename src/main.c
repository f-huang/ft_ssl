/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 10:49:46 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/07 13:57:11 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <ft_ssl.h>

static void	print_commands_usage(void)
{
	const t_command_keeper	*commands;
	uint8_t			i;

	commands = get_commands();
	ft_putstr_fd("\nCommands\n", 2);
	i = 0;
	while (commands[i].name)
	{
		ft_putendl_fd(commands[i].name, 2);
		++i;
	}
}

static int	ssl_handle_error(uint8_t error_code, const char *str)
{
	if (error_code == SSL_ERROR_USAGE)
		ft_putstr_fd("usage: ft_ssl command\n", 2);
	else if (error_code == SSL_ERROR_COMMAND_NOT_FOUND)
	{
		ft_putstr_fd("ft_ssl: Error: '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("' is an invalid command.\n", 2);
	}
	print_commands_usage();
	return (EXIT_FAILURE);
}

int			main(int ac, char **av)
{
	t_command_keeper		command;
	int				error;

	ft_bzero(&command, sizeof(t_command_keeper));
	command = find_command(av[1]);
	if (ac < 2 || command.name == NULL)
		return (ssl_handle_error(\
			ac < 2 ? SSL_ERROR_USAGE : SSL_ERROR_COMMAND_NOT_FOUND, av[1]));
	error = command.handle_command(ac, av, command);
	return (error == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
