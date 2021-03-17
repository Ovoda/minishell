/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 20:42:02 by calide-n          #+#    #+#             */
/*   Updated: 2021/03/17 10:26:30 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# include "header.h"

typedef int		t_bool;

typedef struct	s_list
{
	struct s_list	*next;
	void			*data;
}				t_list;

typedef struct	s_var
{
	char	*name;
	char	*content;
	int		is_define;
}				t_var;

typedef struct	s_lexer
{
	int		i;
	char	*line;
	int		x;
	int		begin;
}				t_lexer;

typedef struct	s_word
{
	char	*content;
	int		sep;
	int		space;
	int		type;
	int		builtin;
}				t_word;

typedef struct	s_node
{
	struct s_node	*right;
	struct s_node	*left;
	int				type;
	char			*file_name;
	int				fd;
	int				pfd[2];
	int				redi_type;
	char			*cmd;
	char			**args;
}				t_node;

typedef struct	s_saver
{
	t_list	*envp_list;
	int		*past_pfd;
	int		*current_pfd;
}				t_saver;

typedef struct	s_env_str
{
	char	*var;
	char	*before_var;
	char	*after_var;
	int		quote;
}				t_env_str;

typedef struct	s_ast_var
{
	int	i;
	int	index;
}				t_ast_var;

#endif
