/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:29:38 by majosue           #+#    #+#             */
/*   Updated: 2021/11/18 17:57:28 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include "libft.h"
# include <signal.h>

# define ZERO		SIGUSR1
# define ONE			SIGUSR2
# define NEXT		SIGUSR1
# define DONE		SIGUSR2
# define MESSAGE_LEN	2048

struct s_message
{
	char	*str;
	size_t	i;
	size_t	size;
};

struct s_char
{
	char	c;
	uint8_t	bits;
};

void	reset_char(struct s_char *current_char);
void	reset_message(struct s_message *message);
void	enlarge_message(struct s_message *message);
void	add_char(struct s_message *message, char c);
int		set_pid(int current_pid, int pid, struct s_char *current_char, \
											struct s_message *message);

#endif
