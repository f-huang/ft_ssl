/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 10:49:46 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/28 19:47:03 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_ssl.h>

static void	print_commands_usage(void)
{
	const t_command	*commands;
	uint8_t			i;

	commands = get_commands();
	ft_putendl("\nCommands");
	i = 0;
	while (commands[i].name)
	{
		ft_putendl(commands[i].name);
		++i;
	}
}

static int	ssl_handle_error(uint8_t error_code, const char *str)
{

	if (error_code == SSL_ERROR_USAGE)
		ft_printf_fd(2, "usage: ft_ssl command\n");
	else if (error_code == SSL_ERROR_COMMAND_NOT_FOUND)
		ft_printf_fd(2, "ft_ssl:Error: '%s' is an invalid command.\n", str);
	print_commands_usage();
	return (1);
}

int		main(int ac, char **av)
{
	t_command		command;
	int				i;
	uint8_t			stop_option;

	command = find_command(av[1]);
	if (command.name == NULL)
		return (ssl_handle_error(\
			ac < 2 ? SSL_ERROR_USAGE : SSL_ERROR_COMMAND_NOT_FOUND,\
			av[1]\
		));
	stop_option = 0;
	i = 0;
	if (ac == 2)
		command.start(av, &i, &stop_option);
	else
	{
		i = 2;
		while (av[i])
		{
			if (ft_strequ("--", av[i]))
				stop_option = 1;
			else
				if (command.start(av, &i, &stop_option) == -1)
					return (1);
			++i;
		}
	}
	return (0);
}
