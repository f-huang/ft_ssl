/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_wchar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 19:36:48 by fhuang            #+#    #+#             */
/*   Updated: 2017/10/19 11:50:25 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

char			*mask(char *str, int n_octet, int signif_bits)
{
	char	ret[n_octet * 8 + 1];
	char	*patt;
	int		j;

	ft_memset(ret, '\0', n_octet * 8 + 1);
	if (n_octet == 1)
		patt = MASK1;
	else if (n_octet == 2)
		patt = MASK2;
	else if (n_octet == 3)
		patt = MASK3;
	else
		patt = MASK4;
	j = ft_strlen(patt);
	while (j-- >= 0)
	{
		if (patt[j] == 'x')
			ret[j] = signif_bits >= 0 ? str[signif_bits--] : '0';
		else
			ret[j] = patt[j];
	}
	return (ft_strdup(ret));
}

int				get_n_octet(char **tmp, wchar_t c, int *signif_bits)
{
	*tmp = ft_printf_itoa_base((unsigned int)c, 2, 1);
	if (*tmp == NULL)
		exit(EXIT_FAILURE);
	*signif_bits = ft_strlen(*tmp);
	if (*signif_bits <= 7)
		return (1);
	else if (*signif_bits <= 11)
		return (2);
	else if (*signif_bits <= 16)
		return (3);
	return (4);
}

unsigned char	*convert_to_utf8(char *binary, int n_octet)
{
	int				i;
	char			*tmp;
	int				*ret;
	unsigned char	toto[n_octet + 1];

	tmp = NULL;
	if ((ret = (int*)ft_memalloc(sizeof(int) * n_octet)) == NULL)
		exit(EXIT_FAILURE);
	ft_memset(toto, 0, n_octet + 1);
	i = -1;
	while (++i < n_octet)
	{
		tmp = ft_strndup(binary + (8 * i), 8);
		ret[i] = ft_atoi_base(tmp, 2);
		toto[i] = ret[i];
		if (tmp != NULL)
			ft_strdel(&tmp);
	}
	if (binary != NULL)
		ft_strdel(&binary);
	if (ret != NULL)
		ft_memdel((void**)&ret);
	return ((unsigned char*)ft_strdup((char*)toto));
}

unsigned char	*transform_wchar(wchar_t wchar, int *count)
{
	int				n_octet;
	char			*tmp;
	char			*binary;
	int				signif_bits;

	tmp = NULL;
	binary = NULL;
	n_octet = get_n_octet(&tmp, wchar, &signif_bits);
	*count += n_octet;
	if ((binary = mask(tmp, n_octet, signif_bits - 1)) == NULL)
		exit(EXIT_FAILURE);
	if (tmp != NULL)
		ft_strdel(&tmp);
	return (convert_to_utf8(binary, n_octet));
}

unsigned char	*transform_wstr(t_print *link, wchar_t *wstr)
{
	int				i;
	int				count;
	char			*ret;
	char			*ptr;

	if ((ret = ft_strnew(sizeof(wchar_t) * ft_wcslen(wstr))) == NULL)
		exit(EXIT_FAILURE);
	count = 0;
	i = 0;
	while (wstr[i])
	{
		if ((ptr = (char*)transform_wchar(wstr[i], &count)) == NULL)
			exit(EXIT_FAILURE);
		if (E_TYPE == T_WSTR && PRECISION && count > PRECISION)
		{
			if (ptr != NULL)
				ft_strdel(&ptr);
			break ;
		}
		ft_strcat(ret, ptr);
		if (ptr != NULL)
			ft_strdel(&ptr);
		i++;
	}
	return ((unsigned char*)ret);
}
