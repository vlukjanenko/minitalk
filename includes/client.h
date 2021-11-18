/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:29:38 by majosue           #+#    #+#             */
/*   Updated: 2021/11/18 14:34:46 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H
# include "libft.h"
# include <signal.h>

#define ZERO		SIGUSR1

struct s_message
{
	int			pid;
	const char	*str;
};


#endif
