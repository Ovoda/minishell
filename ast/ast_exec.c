/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <mlarboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:02:08 by mlarboul          #+#    #+#             */
/*   Updated: 2021/03/21 16:04:55 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_is_cmd(char *str)
{
	struct stat stats;

	if (stat(str, &stats) == 0)
		return (1);
	ft_putstr("msh: ");
	ft_putstr(str);
	ft_putstr(": command not found\n");
	return (0);
}

int		exec_arg_fork(t_node *node, t_saver *saver, int flag)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		printf("Process issues.\n");
		return (-1);
	}
	if (pid == 0)
	{
		node->envp = list_to_tabs(saver->envp_list, 0);
		if (node->pfd_input != STDOUT)
		{
			close(0);
			dup(node->pfd_input);
		}
		if (node->pfd_output != STDIN)
		{
			close(1);
			dup(node->pfd_output);
		}
		if (ft_is_builtin(node->word[0].content))
			exit(exec_builtins(node->word, saver->envp_list));
		else if (ft_is_cmd(node->args[0]))
			execve(node->args[0], node->args, node->envp);
		exit(127);
	}
	g_proc.pid[g_proc.index] = pid;
	g_proc.index++;
	return (0);
}

int		exec_arg(t_node *node, t_saver *saver, int flag)
{
	int	ret;

	if (ft_strcmp(node->word[0].content, "echo") != 0)
		g_proc.ret = -1;
	if (ft_strcmp(node->word[0].content, "cd") == 0
			|| (ft_strcmp(node->word[0].content, "export") == 0 && 
				!node->word[1].content)
			|| ft_strcmp(node->word[0].content, "unset") == 0 ||
			ft_strcmp(node->word[0].content, "exit") == 0)
	{
		ret = exec_builtins(node->word, saver->envp_list);
		if (ret == -2)
			return (-2);
		g_proc.ret = ret; 
		return (2);
	}
	exec_arg_fork(node, saver, flag);
	if (node->pfd_input != STDOUT)
		close(node->pfd_input);
	if (node->pfd_output != STDIN)
		close(node->pfd_output);
	return (0);
}

int		exec_node(t_node *node, t_saver *saver, int flag)
{
	if (node->type == ARG)
		return (exec_arg(node, saver, flag));
	return (0);
}


int	btree_prefix_exec(t_node *node, t_saver *saver, int flag)
{
	int	ret;

	if (!node)
		return (-1);
	ret = exec_node(node, saver, flag);
	if (node->left)
		ret = btree_prefix_exec(node->left, saver, 1);
	if (node->right)
		ret = btree_prefix_exec(node->right, saver, 0);
	return (ret);
}