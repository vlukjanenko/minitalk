/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:28:43 by majosue           #+#    #+#             */
/*   Updated: 2021/11/18 14:40:33 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	reset_char(struct s_char *current_char)
{
	current_char->c = 0;
	current_char->bits = 0;
}

void	reset_message(struct s_message *message)
{
	ft_strdel(&message->str);
	message->str = NULL;
	message->i = 0;
	message->size = 0;
}

void	enlarge_message(struct s_message *message)
{
	char	*new_str;

	message->size += MESSAGE_LEN;
	new_str = (char *)ft_memalloc(sizeof(*new_str) * message->size);
	if (new_str == NULL)
	{
		write(2, "Out of memory\n", 14);
		ft_strdel(&message->str);
		exit (1);
	}
	ft_strncpy(new_str, message->str, message->i);
	ft_strdel(&message->str);
	message->str = new_str;
}

int	set_pid(int current_pid, int pid, struct s_char *current_char, \
											struct s_message *message)
{
	if (!current_pid)
		current_pid = pid;
	else if (current_pid != pid)
	{
		write(2, "Previous connection reset, new client connected\n", 48);
		current_pid = pid;
		reset_char(current_char);
		reset_message(message);
	}
	return (current_pid);
}

void	add_char(struct s_message *message, char c)
{
	if (message->str == NULL || message->i == message->size - 1)
		enlarge_message(message);
	message->str[message->i++] = c;
}
