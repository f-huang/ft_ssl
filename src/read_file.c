/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 20:14:11 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/28 20:40:00 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <libft.h>

#define BUFFER_SIZE 1

static int	handle_file_error(const char *path, const char *command)
{
	ft_printf_fd(2, "%s: %s: Could not open/read/close file or directory.\n",
		command,
		path);
	return (1);
}

int			read_file(const char *path,
					const char *command,
					int options,
					void (*hash)(char *, int))
{
	int		fd;
	int		ret;
	char	*file_content;
	char	buffer[BUFFER_SIZE + 1];

	ft_putstr("Reading file : ");
	ft_putendl(path);
	file_content = NULL;
	if ((fd = open(path, O_RDONLY)) == -1)
		return (handle_file_error(path, command));
	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		if (file_content)
			file_content = ft_strjoin_free(file_content, buffer);
		else
			file_content = ft_strdup(buffer);
	}
	if (close(fd) == -1 || ret == -1)
		return (handle_file_error(path, command));
	hash(file_content, options);
	ft_strdel(&file_content);
	return (0);
}
