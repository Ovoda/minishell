/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 09:40:39 by calide-n          #+#    #+#             */
/*   Updated: 2021/02/23 20:00:14 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_word	get_next_word(char *str, int on, int *ret);
int	get_nb_word(char *str, int on);

int	ft_count_lines()
{
	int nb;
	char *line;

	nb = 0;
	while (get_next_line(0, &line) != 0)
		nb++;
	return (nb);
}

int	ft_bksl(char *str)
{
	int i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
		i++;
	if (str[i - 1] == '\'')
		return (1);
	return (0);
}

int	ft_nb_blocks(char *str)
{
	int i;
	int quote;
	int nb;

	i = 0;
	nb = 0;
	quote = 0;
	if (str[i])
		nb++;
	while (str[i])
	{
		if (str[i] == '\'' && quote == 0)
			quote = 1;
		if (str[i] == '"' && quote == 0)
			quote = 2;
		if (str[i] == ';' && quote == 0)
		{
			i++;
			while (str[i] == ' ')
				i++;
			if (str[i] == '\0')
				break;
			nb++;
		}
		i++;
	}
	return (nb);
}

t_word	*ft_word(char *line, int reset)
{
	int ret;
	int windex;
	int nb;
	t_word *word;
	int new_line;

	windex = 0;
	ret = 1;
	nb = 0;
	while (get_nb_word(line, reset) != 0)
	{
		nb++;
		reset = 1;
	}
	new_line = reset;
	word = malloc(sizeof(t_word) * (nb + 1));
	while (ret)
	{
		word[windex] = get_next_word(line, new_line, &ret);
		new_line = 1;
		if (word[windex].content)
		{
			if (ft_strcmp(word[windex].content, ";") == 0)
				break;
		}
		windex++;
	}
	return (word);
}

int	main(int argc, char **argv)
{
	char 	*line;
	int		nb_blocks;
	t_block	*block;
	int		reset;

	get_next_line(0, &line);
	nb_blocks = ft_nb_blocks(line);
	block = (t_block *)malloc(sizeof(t_block) * (nb_blocks + 1));
	int index = 0;
	reset = 0;
	while (index < nb_blocks)
	{
		block[index].word = ft_word(line, reset);
		reset = 1;
		index++;	
	}
	index = 0;
	int windex = 0;
	while (index < nb_blocks)
	{
		windex = 0;
		printf("%d [", index);
		while (block[index].word[windex].content)
		{
			printf(" [%s]", block[index].word[windex].content);
			windex++;
		}
		printf(" ]\n");
		reset = 1;
		index++;	
	}
	free(line);
	return (0);
}
