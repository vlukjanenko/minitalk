/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:30:21 by majosue           #+#    #+#             */
/*   Updated: 2021/11/14 19:35:32 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

struct s_messages	g_message;

static void	reset_char(void)
{
	g_message.pos = 0;
	g_message.bit = 0;
	g_message.c = 0;
}

static void	enlarge_str(void)
{
	char	*new_str;
	size_t	i;

	i = 0;
	g_message.size += STR_LEN;
	new_str = (char *)ft_memalloc(sizeof(char) * g_message.size);
	if (!new_str)
	{
		ft_dprintf(2, "Out of memory\n");
		exit (1);
	}
	ft_strncpy(new_str, g_message.str, g_message.i);
	ft_strdel(&g_message.str);
	g_message.str = new_str;
}

void	bit_up(int signum, siginfo_t *siginfo, void *code)
{
	(void)signum;
	(void)siginfo;
	(void)code;
	g_message.bit = 1;
}

void	bit_shift(int signum, siginfo_t *siginfo, void *code)
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
		g_message.str[g_message.i++] = g_message.c;
		if (g_message.i == g_message.size - 1)
			enlarge_str();
		reset_char();
	}
	else if (g_message.pos == 8 && !g_message.c)
	{
		g_message.str[g_message.i] = '\n';
		write(1, g_message.str, g_message.i + 1);
		reset_char();
		g_message.i = 0;
		ft_kill(siginfo->si_pid, SIGUSR2);
	}
}

int	main(void)
{
	struct sigaction	usr1;
	struct sigaction	usr2;

	usr1.sa_sigaction = bit_up;
	usr1.sa_flags = SA_SIGINFO;
	usr2.sa_sigaction = bit_shift;
	usr2.sa_flags = SA_SIGINFO;
	sigemptyset(&usr1.sa_mask);
	sigaddset(&usr1.sa_mask, SIGUSR2);
	sigemptyset(&usr2.sa_mask);
	sigaddset(&usr2.sa_mask, SIGUSR1);
	sigaction(SIGUSR1, &usr1, NULL);
	sigaction(SIGUSR2, &usr2, NULL);
	ft_printf("pid: %d\n", getpid());
	g_message.size = STR_LEN;
	g_message.str = (char *)ft_memalloc(sizeof(char) * STR_LEN);
	if (!g_message.str)
	{
		ft_dprintf(2, "Out of memory");
		return (1);
	}
	while (1)
		pause();
	return (0);
}
