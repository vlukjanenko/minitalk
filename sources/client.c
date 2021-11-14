/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 08:37:14 by majosue           #+#    #+#             */
/*   Updated: 2021/11/14 10:30:30 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <signal.h>

void send_message(int pid, char *message)
{
	int i;

	i = 0;
	while (*message)
	{
		while (i < 8)
		{
			if (((*message >> i) & 1))
			{
				kill(pid, SIGUSR1);
				usleep(10);
			}
			kill(pid, SIGUSR2);
			usleep(10);
			i++;
		}
		i = 0;
		message++;
	}
	while (i < 8)
		{
			if (((*message >> i) & 1))
			{
				kill(pid, SIGUSR1);
				usleep(10);
			}
			kill(pid, SIGUSR2);
			usleep(10);
			i++;
		}
		i = 0;
}

void f(int signum, siginfo_t * siginfo, void *code)
{
	(void)signum;
	(void)siginfo;
	(void)code;
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*message;

	struct sigaction usr1;
	struct sigaction usr2;
	usr1.sa_sigaction = f;
	usr2.sa_sigaction = f;
	usr1.sa_flags = SA_SIGINFO;
	usr2.sa_flags = SA_SIGINFO;
	sigemptyset(&usr1.sa_mask);
	sigaddset(&usr1.sa_mask, SIGUSR2);
	sigemptyset(&usr2.sa_mask);
	sigaddset(&usr2.sa_mask, SIGUSR1);
	sigaction(SIGUSR1, &usr1, NULL);
	sigaction(SIGUSR2, &usr2, NULL);
	if (argc < 3)
	{
		ft_printf("usage: ./client pid message\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	message = argv[2];
	ft_printf("pid = %d\n", getpid());
	//signal(SIGUSR1, f);
	send_message(pid, message);
	/* for (int i = 0; i < 8; i++)
	{
		kill(pid, SIGUSR1);
		pause();
	} */
	return (0);
}
