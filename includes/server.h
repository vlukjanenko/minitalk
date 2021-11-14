/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:29:38 by majosue           #+#    #+#             */
/*   Updated: 2021/11/14 20:19:09 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include "libft.h"
# include <signal.h>

# define STR_LEN 512

struct s_messages
{
	char	*str;
	size_t	i;
	size_t	size;
	int		bit;
	int		pos;
	char	c;
};

void	ft_kill(int pid, int sig);

#endif
