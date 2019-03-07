/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_digest.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:13:47 by fhuang            #+#    #+#             */
/*   Updated: 2019/03/07 14:34:54 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_DIGEST_H
# define MESSAGE_DIGEST_H

# define ERROR_ILLEGAL_OPTION -2
# define ERROR_OPTION_REQUIRES_ARGUMENT -3

# define MESSAGE_DIGEST_OPTIONS "pqrsv"

# define OPTION_PRINT (1 << 1)
# define OPTION_QUIET (1 << 2)
# define OPTION_REVERSE (1 << 3)
# define OPTION_VERBOSE (1 << 4)
# define OPTION_STRING (1 << 5)


#endif
