/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:48:07 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/07 14:37:55 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <ft_ssl.h>

const t_command_keeper		*get_commands(void)
{
	static const t_command_keeper	commands[] = {
		{MESSAGE_DIGEST, MD5, STRINGIFY(MD5), handle_command_message_digest, md5_hash},
		{MESSAGE_DIGEST, SHA256, STRINGIFY(SHA256), handle_command_message_digest, sha256_hash},
		{-1, -1, NULL, NULL, NULL}
	};

	return (commands);
}
