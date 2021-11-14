/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:30:21 by majosue           #+#    #+#             */
/*   Updated: 2021/11/14 10:30:22 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <signal.h>

void terminate(int param)
{
	ft_printf("Завершение программы %d...\n", param);
}

int				g_sig[30];
int				g_i = 0;
int				g_a = 1;
int				g_pid;

struct s_messages
{
	int		bit;
	int		pos;
	char	c;
};
struct s_messages g_message;

char g_string[10000];
int	 g_index;

void bit_up(int signum, siginfo_t * siginfo, void *code)
{
	(void)signum;
	(void)siginfo;
	(void)code;

	g_message.bit = 1;
	g_pid = siginfo->si_pid;
	//ft_printf("SIGUSR1 HANDLER si_pid = %d\n", siginfo->si_pid);
	//ft_printf("%d - %d\n", siginfo->si_pid, signum);
	//kill(siginfo->si_pid, SIGUSR1);
}

void bit_shift(int signum, siginfo_t * siginfo, void *code)
{
	(void)signum;
	(void)siginfo;
	(void)code;
	if (g_message.bit)
	{
		g_message.c = g_message.c | (1 << g_message.pos);
		g_message.bit = 0;
	}
	g_message.pos++;
	if (g_message.pos == 8 && g_message.c)
	{
		g_string[g_index++] = g_message.c;
		g_message.pos = 0;
		g_message.bit = 0;
		g_message.c = 0;
	}
	else if (g_message.pos == 8 && !g_message.c)
	{
		g_string[g_index] = '\n';
		write(1, g_string, g_index + 1);
		g_index = 0;
		g_message.pos = 0;
		g_message.bit = 0;
	}
}

void term(int sig)
{
	(void)sig;
	for(int i = 0; i < 30; i++)
	{
		ft_printf("pid = %d\n", g_sig[i]);
	}
	g_a = 0;
}

int	main(void)
{
	struct sigaction usr1;
	struct sigaction usr2;
	int	pid;
	usr1.sa_sigaction = bit_up;
	usr1.sa_flags = SA_SIGINFO;
	usr2.sa_sigaction = bit_shift;
	usr2.sa_flags = SA_SIGINFO;
	sigemptyset(&usr1.sa_mask);
	sigaddset(&usr1.sa_mask, SIGUSR2);
	sigaddset(&usr1.sa_mask, SIGUSR1);
	sigemptyset(&usr2.sa_mask);
	sigaddset(&usr2.sa_mask, SIGUSR1);
	sigaddset(&usr2.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &usr1, NULL);
	sigaction(SIGUSR2, &usr2, NULL);
	pid = getpid();
	ft_printf("pid: %d\n", pid);
	while(1)
	{
		pause();
	}
	return (0);
}
