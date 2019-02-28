/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 16:15:35 by fhuang            #+#    #+#             */
/*   Updated: 2017/11/03 18:10:30 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

t_list	*get_fd(t_list **lst, int const fd)
{
	t_list		*ptr;
	t_gnl		gnl;

	ptr = *lst;
	while (ptr)
	{
		if (fd == (((t_gnl*)(ptr->content))->fd))
			return (ptr);
		ptr = ptr->next;
	}
	ft_bzero(&gnl, sizeof(t_gnl));
	gnl.fd = (int)fd;
	if ((gnl.lfo = ft_strnew(BUFF_SIZE)))
	{
		ptr = ft_lstnew(&gnl, sizeof(gnl));
		if (ptr)
			ft_lstadd(lst, ptr);
		return (*lst);
	}
	else
		return (0);
}

int		read_fd(t_list *lst, int const fd)
{
	int		ret;
	int		save;
	char	buf[BUFF_SIZE + 1];
	char	*tmp;

	ret = 1;
	save = 0;
	while ((ft_strchr(((t_gnl*)(lst->content))->lfo, '\n') == 0)
			&& (ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		if (ft_strchr(((t_gnl*)(lst->content))->lfo, '\n') == 0)
			save = ret;
		buf[ret] = '\0';
		tmp = ((t_gnl*)(lst->content))->lfo;
		((t_gnl*)(lst->content))->lfo =
					ft_strjoin(((t_gnl*)(lst->content))->lfo, buf);
		ft_strdel(&tmp);
		if (!((t_gnl*)(lst->content))->lfo)
			return (-1);
	}
	return (save ? save : ret);
}

int		free_list(t_list **lst, t_list *tmp)
{
	t_list	*lst_next;
	t_list	*ptr;

	ptr = *lst;
	if (tmp && *lst)
		while (ptr)
		{
			lst_next = ptr->next;
			if (((t_gnl*)(ptr->content))->fd == ((t_gnl*)(tmp->content))->fd)
			{
				ptr = lst_next;
				free(((t_gnl*)(tmp->content))->lfo);
				free(tmp);
			}
			ptr = lst_next;
		}
	return (0);
}

int		update_lfo(t_list **lst, char **line, t_list *tmp, int ret)
{
	int		len;
	char	*lfo;

	lfo = (((t_gnl*)(tmp->content))->lfo);
	if (ft_strchr(lfo, '\n') == 0)
	{
		if ((*line = ft_strdup(lfo)) == 0)
			return (-1);
		if ((!ret && !ft_strlen(lfo)))
			return (free_list(lst, tmp));
		ft_strclr((((t_gnl*)(tmp->content))->lfo));
		return (1);
	}
	len = ft_strlen(lfo) - ft_strlen(ft_strstr(lfo, "\n"));
	if ((*line = ft_strndup(lfo, len)))
		if ((((t_gnl*)(tmp->content))->lfo =
					ft_strdup(ft_strchr(lfo, '\n') + 1)))
			return (!ret ? free_list(lst, tmp) : 1);
	return (-1);
}

int		get_next_line(int const fd, char **line)
{
	static t_list	*lst = NULL;
	int				ret;
	t_list			*tmp;

	if (fd < 0 || BUFF_SIZE <= 0 || line == NULL)
		return (-1);
	tmp = get_fd(&lst, fd);
	if ((ret = read_fd(tmp, fd)) == -1)
		return (-1);
	return (update_lfo(&lst, line, tmp, ret));
}
