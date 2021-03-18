/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <mlarboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:02:08 by mlarboul          #+#    #+#             */
/*   Updated: 2021/03/15 17:59:16 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		pipe_arg(t_node *node, t_saver *saver, int flag)
{
	node->input = 0;
	node->output = 1;
	if (saver->past_pfd == NULL)
		node->pfd_output = saver->curr_pfd[1];
	else
	{
		if (flag == 1)
		{
			node->pfd_input = saver->past_pfd[0];
			node->pfd_output = saver->curr_pfd[1];
		}
		else
		{
			node->pfd_input = saver->past_pfd[0];
		}
	}
	return (0);
}

int		pipe_pipe(t_node *node, t_saver *saver)
{
	if (saver->current_pfd != NULL)
		saver->past_pfd = saver->curr_pfd;
	else
		saver->past_pfd = NULL;
	if (pipe(node->pfd) < 0)
	{
		printf("Pipe issues.\n");
		return (-1);
	}
	saver->curr_pfd = node->pfd;
	return (0);
}

int		pipe_node(t_node *node, t_saver *saver, int flag)
{
	if (node->type == PIPE)
		pipe_pipe(node, saver);
//	else if(node->type == REDI)
//		execute_arg(node, saver);
	else if (node->type == ARG)
		pipe_arg(node, saver, flag);
	return (0);
}


void	btree_prefix_pipe(t_node *node, t_saver *saver, int flag)
{
	if (!node)
		return ;
	pipe_node(node, saver, flag);
	if (node->left)
		btree_prefix_exec(node->left, saver, 1);
	if (node->right)
		btree_prefix_exec(node->right, saver, 0);
}
