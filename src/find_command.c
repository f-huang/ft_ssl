/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:48:07 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/05 18:25:10 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_ssl.h>

t_command_keeper		find_command(char *command)
{
	uint8_t					i;
	const t_command_keeper			*commands;

	i = 0;
	commands = get_commands();
	while (command && commands[i].name)
	{
		if (ft_strequ(commands[i].name, ft_strupper(command)))
			return (commands[i]);
		++i;
	}
	return (commands[i]);
}
