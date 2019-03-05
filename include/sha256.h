/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:18:28 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/05 19:03:10 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# include <stdint.h>
# include <ft_ssl.h>

# define SHA_OPTIONS "pqrsv"

# define SHA_COMMAND "SHA256"

# define OPTION_PRINT (1 << 0)
# define OPTION_QUIET (1 << 1)
# define OPTION_REVERSE (1 << 2)
# define OPTION_VERBOSE (1 << 3)


int				sha256_start(char **av,
						int *i,
						uint8_t *stop_option,
						const char *command_name);
void			sha256_execute_hash(t_reader reader, int options);
const uint32_t	*sha256_get_round_constants(void);

#endif
