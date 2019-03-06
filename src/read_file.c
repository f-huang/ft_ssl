/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 20:14:11 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/06 20:41:04 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>
#include <ft_ssl.h>

#define BUFFER_SIZE 1024

static int	handle_file_error(const char *path, const char *command)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	if (path)
		ft_putstr_fd(path, 2);
	ft_putstr_fd(": Could not open/read/close file or directory.\n", 2);
	return (1);
}
#include <stdio.h>
int			read_file(const char *path,
					const char *command,
					uint32_t options,
					void (*hash)(t_reader, uint32_t))
{
	int			fd;
	int			ret;
	t_reader	reader;
	void		*tmp;
	char		buffer[BUFFER_SIZE + 1];

	fd = 0;
	ft_bzero(&reader, sizeof(t_reader));
	reader.type = ARG_FILE;
	reader.name = path;
	if (path && (fd = open(path, O_RDONLY)) == -1)
		return (handle_file_error(path, command));
	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		if (reader.content)
		{
			tmp = reader.content;
			if ((reader.content = ft_memalloc(reader.size + ret + 1)))
			{
				ft_memcpy(reader.content, tmp, reader.size);
				ft_memcpy(reader.content + reader.size, buffer, ret);
			}
			ft_memdel(&tmp);
		}
		else
			reader.content = ft_memdup(buffer, ret + 1);
		reader.size += ret;
	}
	if (close(fd) == -1 || ret == -1)
		return (handle_file_error(path, command));
	hash(reader, options);
	ft_memdel(&reader.content);
	return (0);
}
