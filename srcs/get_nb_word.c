/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nb_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:41:04 by calide-n          #+#    #+#             */
/*   Updated: 2021/02/24 15:35:34 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/header.h"

int	ft_check_next_quote_count(char *str, int i, char c)
{
	while (str[i] != c)
		if (str[i++] == '\0')
			return (0);
	return (1);
}

void	ft_manage_quote_count(char *str, int *i, char c)
{

	*i += 1;
	if (!ft_check_next_quote_count(str, *i, c))
	{
		printf("Error quote\n");
		return ;
	}
	while (str[*i] && str[*i] != c)
	{
		*i += 1;
	}
	*i += 1;
}

void	ft_manage_space_count(char *str, int *i)
{
	while (str[*i] && str[*i] != ' ' && str[*i] != '\'' && str[*i] != '"' && str[*i] != ';' && str[*i] != '=')
		*i += 1;
	if (str[*i] != '\'' && str[*i] != '"' && str[*i] != ';' && str[*i] != '=')
		*i += 1;
}

int	get_nb_word(char *str, int on)
{
	static int	i;
	int			k;
	int			j;

	k = 0;
	j = 0;
	if (on == 0)
		i = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] == ' ')
		i++;
	if (str[i] == ';')
	{
		i++;
		return (2);
	}
	if (str[i] == '=' || str[i] == '|' || str[i] == '<' || str[i] == '>')
	{
		i++;
		return (1);
	}
	else if (str[i] != '\'' && str[i] != '"')
		ft_manage_space_count(str, &i);
	else if (str[i] == '\'')
		ft_manage_quote_count(str, &i, '\'');
	else if (str[i] == '"')
		ft_manage_quote_count(str, &i, '"');
	while (str[i] == ' ')
		i++;
	return (1);
}