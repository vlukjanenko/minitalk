/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 08:37:14 by majosue           #+#    #+#             */
/*   Updated: 2021/11/14 20:16:59 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	ft_kill2(int pid, int sig)
{
	kill(pid, sig);
	usleep(10);
}

static void	send_message(int pid, char *message)
{
	int	i;

	i = 0;
	while (*message)
	{
		while (i < 8)
		{
			if (((*message >> i) & 1))
				ft_kill2(pid, SIGUSR1);
			ft_kill2(pid, SIGUSR2);
			i++;
		}
		i = 0;
		message++;
	}
	while (i < 8)
	{
		if (((*message >> i) & 1))
			ft_kill2(pid, SIGUSR1);
		ft_kill2(pid, SIGUSR2);
		i++;
	}
	i = 0;
}

static void	ft_done(int signum, siginfo_t *siginfo, void *code)
{
	(void)signum;
	(void)siginfo;
	(void)code;
	ft_printf("Confirm signal received\n");
	exit(0);
}

int	main(int argc, char **argv)
{
	int					pid;
	char				*message;
	struct sigaction	usr2;

	usr2.sa_sigaction = ft_done;
	usr2.sa_flags = SA_SIGINFO;
	sigemptyset(&usr2.sa_mask);
	sigaction(SIGUSR2, &usr2, NULL);
	if (argc < 3)
	{
		ft_printf("usage: ./client pid message\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	message = argv[2];
	send_message(pid, message);
	sleep(1);
	ft_printf("Timout response from server\n");
	return (1);
}
