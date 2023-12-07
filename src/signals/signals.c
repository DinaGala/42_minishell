/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:32:18 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/02 18:00:26 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sig_handler(int sig)
{
	printf("\n");
	rl_on_new_line();
//	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

void	signals(void)
{
//	rl_catch_signals = 0;
	signal(SIGINT, sig_handler); // ctrl + C
	signal(SIGQUIT, SIG_IGN);  // ctrl + D
}