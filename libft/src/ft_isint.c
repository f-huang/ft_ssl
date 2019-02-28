/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 12:31:35 by fhuang            #+#    #+#             */
/*   Updated: 2017/11/03 19:00:13 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

int			ft_isint(const char *str)
{
	return (ft_strlen(str) < 12 &&\
		INT_MIN <= ft_atol(str) && ft_atol(str) <= INT_MAX);
}
