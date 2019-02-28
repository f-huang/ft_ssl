/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:48:07 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/28 19:32:32 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <ft_ssl.h>
#include <md5.h>

const t_command		*get_commands(void)
{
	static const t_command	commands[] = {
		{STRINGIFY(MD5), MD5, MD5_OPTIONS, md5_start},
		// {STRINGIFY(SHA256), SHA256},
		// {STRINGIFY(SHA512), SHA512},
		// {STRINGIFY(WHILRPOOL), WHIRLPOOL},
		{NULL, -1, NULL, NULL}
	};

	return (commands);
}
