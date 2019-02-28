/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str3join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 15:50:46 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/15 15:25:27 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str3join(const char *s1, const char *s2, const char *s3)
{
	char	*ret;

	if (!s1 || !s2 || !s3)
		return (NULL);
	ret = ft_strndup(s1, ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3));
	if (ret == NULL)
		return (NULL);
	ret = ft_strcat(ret, s2);
	ret = ft_strcat(ret, s3);
	return (ret);
}
