/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:00:40 by majosue           #+#    #+#             */
/*   Updated: 2021/11/18 14:39:43 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	build_message(int bit, int pid)
{
	static int				current_pid;
	static struct s_message	message;
	static struct s_char	current_char;

	current_pid = set_pid(current_pid, pid, &current_char, &message);
	current_char.c = current_char.c | bit << current_char.bits;
	if (current_char.bits == 7 && current_char.c)
	{
		add_char(&message, current_char.c);
		reset_char(&current_char);
	}
	else if (current_char.bits == 7 && !current_char.c)
	{
		add_char(&message, '\n');
		write(1, message.str, message.i);
		reset_char(&current_char);
		reset_message(&message);
		current_pid = 0;
		return (DONE);
	}
	else
		current_char.bits++;
	return (NEXT);
}

void	receive(int sig, siginfo_t *siginfo, void *ucontext)
{
	int	confirm_signal;
	int	error;

	(void)ucontext;
	confirm_signal = build_message(1 + sig - ONE, siginfo->si_pid);
	error = kill(siginfo->si_pid, confirm_signal);
	if (error == -1)
	{
		write(2, "Error: connection to client lost\n", 33);
	}
}

int	main(void)
{
	struct sigaction	act;
	struct sigaction	act2;

	act.sa_flags = SA_SIGINFO | SA_NODEFER;
	act2.sa_flags = SA_SIGINFO | SA_NODEFER;
	sigemptyset(&act.sa_mask);
	sigemptyset(&act2.sa_mask);
	act.sa_sigaction = receive;
	act2.sa_sigaction = receive;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act2, NULL);
	ft_printf("%d\n", getpid());
	while (1)
	{
	}
}
