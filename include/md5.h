/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:52:36 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/28 19:44:02 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include <stdint.h>

# define MD5_OPTIONS "pqrs"

# define COMMAND_NAME "md5"

# define OPTION_QUIET (1 << 0)
# define OPTION_REVERSE (1 << 1)


int		md5_start(char **av, int *i, uint8_t *stop_option);

#endif
