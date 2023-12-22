/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:41:40 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/12/22 16:09:18 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
This function initializes the pipe list.
*/
void	pipe_init(t_pipe *pip)
{
	pip->cmd = NULL;
	pip->path = NULL;
	pip->fd_lst = NULL;
	pip->in_fd = -2;
	pip->out_fd = -2;
	pip->builtin = 0;
	pip->next = NULL;
}

/*
This function adds a new pipe node to the end of the pipe list.
*/
void	pipe_add(t_mini *sh, t_pipe *new)
{
	t_pipe	*temp;

	if (!sh->pipe_lst)
	{
		sh->pipe_lst = new;
		return ;
	}
	temp = sh->pipe_lst;
	while (temp -> next)
		temp = temp -> next;
	temp -> next = new;
}

/*
This function cleans the pipe list.
*/
int	pipe_clean(t_pipe **lst)
{
	t_pipe	*temp;

//	printf("[PIPE CLEAN]You entered: PIPE - %p\n", *lst); //erase
	while (*lst)
	{
		temp = (*lst) -> next;
//		printf("[PIPE CLEAN] before hd clean: hd - %p\n", (*lst) -> fd_lst); //erase
		if ((*lst) -> fd_lst)
			fd_clean(&((*lst) -> fd_lst), 0);
		if ((*lst)->in_fd > 0)
			close((*lst)->in_fd);
		if ((*lst)->out_fd > 0)
			close((*lst)->out_fd);
//		printf("[PIPE CLEAN] after hd clean: hd - %p\n", (*lst) -> fd_lst); //erase
//		printf("[PIPE CLEAN] before cmd clean: cmd - %p\n", (*lst) -> cmd); //erase
		if ((*lst)->cmd)
			(*lst)->cmd = arr_clean((*lst)->cmd, 1);
		if ((*lst)->path)
			(*lst)->path = ft_memdel((*lst)->path);
//		printf("[PIPE CLEAN] after cmd clean: cmd - %p\n", (*lst) -> cmd); //erase
		//check if i neet to close in and out fd here
		free(*lst);
		*lst = NULL;
		*lst = temp;
	}
	lst = NULL;
	return (1);
}





