/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:14:05 by majosue           #+#    #+#             */
/*   Updated: 2021/11/18 14:38:25 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

struct s_message	g_message;

int	get_next_signal(void)
{
	static int	bits;
	int			sig;

	if (!*(g_message.str))
		return (ZERO);
	sig = ZERO + ((*(g_message.str) >> bits) & 1);
	if (bits == 7)
	{
		bits = 0;
		g_message.str++;
	}
	else
		bits++;
	return (sig);
}

void	send(int sig, siginfo_t *siginfo, void *ucontext)
{
	int	s;
	int	error;

	(void)sig;
	(void)ucontext;
	(void)siginfo;
	s = get_next_signal();
	error = kill(g_message.pid, s);
	if (error == -1)
	{
		write(2, "Error: invalid pid\n", 19);
		exit(1);
	}
}

void	stop(int sig)
{
	(void)sig;
	write(1, "Server confirm received \n", 25);
	exit(0);
}

int	main(int argc, char **argv)
{
	struct sigaction	act;

	if (argc != 3)
	{
		write(2, "usage: ./client pid \"string\"\n", 29);
		return (1);
	}
	g_message.pid = ft_atoi(argv[1]);
	g_message.str = argv[2];
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = send;
	sigaction(SIGUSR1, &act, NULL);
	signal(SIGUSR2, stop);
	kill(getpid(), SIGUSR1);
	while (1)
	{
	}
}
