/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_for_strings.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 12:11:59 by fhuang            #+#    #+#             */
/*   Updated: 2017/10/19 11:50:38 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static void			transform_flags(t_print *link, char *str, int len)
{
	static void	(*p[5])(t_print *link, char *str, int len, int neg);
	int			i;

	PRECISION >= 0 ? str = ft_strncpy(str, str, PRECISION) : 0;
	LEN = ft_strlen(str) +\
		(((E_TYPE == T_CHAR || E_TYPE == T_WCHAR) && U_VAR.i == 0) ? 1 : 0);
	if (PRECISION >= 0)
		len = WIDTH > (int)ft_strlen(str) ? WIDTH : ft_strlen(str);
	if (E_TYPE == T_VOID)
		PRECISION ? PUSH_FRONT(48, PRECISION - ft_strlen(str)) : 0;
	(C == 'c' || C == 'C') && U_VAR.i == 0 ? len-- : 0;
	p[0] = transform_zero;
	p[1] = transform_plus;
	p[2] = transform_space;
	p[3] = transform_hash;
	p[4] = transform_minus;
	i = -1;
	while (++i < 5)
		(*p[i])(link, str, len, 0);
	len = WIDTH - ft_strlen(str) - ((C == 'c' || C == 'C')\
		&& U_VAR.i == 0 ? 1 : 0);
	WIDTH ? PUSH_FRONT(' ', len) : 0;
	RET = str;
}

static int			get_len(t_print *link, char *ret)
{
	int			len;

	if (!ret)
		exit(EXIT_FAILURE);
	len = ft_strlen(ret);
	len = PRECISION >= len ? PRECISION : len;
	len = WIDTH >= len ? WIDTH : len;
	if (E_TYPE == T_VOID)
		len += 2;
	return (len);
}

static void			get_s_conversion(t_print *link, char **str)
{
	if (PRECISION == 0)
		*str = ft_strdup(U_VAR.s);
	else if (PRECISION == -1)
		*str = ft_strdup("");
	else
		*str = ft_strndup(U_VAR.s, PRECISION);
}

void				transform_for_strings(t_print *link)
{
	char		*ret;
	char		*new;
	int			len;

	ret = NULL;
	new = NULL;
	if ((E_TYPE == T_STR || E_TYPE == T_WSTR) && (!U_VAR.s || !U_VAR.ws))
		ret = PRECISION < 0 ? ft_strdup("") : ft_strdup("(null)");
	else if (E_TYPE == T_WCHAR || E_TYPE == T_WSTR)
		ret = (char*)transform_wstr(link, E_TYPE == T_WSTR ?\
			U_VAR.ws : &U_VAR.wc);
	else if (E_TYPE == T_VOID)
		ret = U_VAR.p == NULL && PRECISION == -1 ? ft_strdup("") :\
		ft_lltoa_base((int64_t)U_VAR.p, 16, 1);
	else if (E_TYPE == T_CHAR)
		ret = ft_strndup((char*)(&U_VAR.i), 1);
	else
		get_s_conversion(link, &ret);
	len = get_len(link, ret);
	if ((new = ft_strnew(len)) == NULL)
		exit(EXIT_FAILURE);
	len ? ft_strcpy(new, ret) : ft_strcpy(new, "");
	if (ret != NULL)
		ft_strdel(&ret);
	transform_flags(link, new, len);
}
