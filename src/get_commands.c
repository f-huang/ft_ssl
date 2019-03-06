/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:48:07 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/06 11:08:28 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <ft_ssl.h>

const t_command		*get_commands(void)
{
	static const t_command	commands[] = {
		{STRINGIFY(MD5), MD5, md5_start},
		{STRINGIFY(SHA256), SHA256, sha256_start},
		// {STRINGIFY(SHA512), SHA512},
		// {STRINGIFY(WHILRPOOL), WHIRLPOOL},
		{NULL, -1, NULL}
	};

	return (commands);
}
