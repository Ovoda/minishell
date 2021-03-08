/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnw_null.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:55:31 by calide-n          #+#    #+#             */
/*   Updated: 2021/03/01 12:55:46 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int ft_manage_null(char c, t_word *word)
{
    if (!c)
    {   
        word->content = NULL;
        return (1);
    }   
    return (0);
}
