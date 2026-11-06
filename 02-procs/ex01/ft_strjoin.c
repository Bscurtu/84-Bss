/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_strjoin.c                                      :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: bscurtu <bscurtu@student.42malaga.com>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/09/22 11:21:00 by bscurtu          #+#    #+#              */
/*   Updated: 2026/09/22 11:21:00 by bscurtu         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	strlen_helper(const char *str)
{
	int	index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

static void	concat_helper(char *str, const char *paste)
{
	int	index;

	index = 0;
	while (str[index] != 0)
		index++;
	while (*paste)
	{
		str[index] = *paste;
		index++;
		paste++;
	}
	str[index] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*new_str;

	size = strlen_helper(s1) + strlen_helper(s2);
	new_str = malloc(sizeof(char) * (size + 1));
	if (!new_str)
		return (NULL);
	while (size + 1 > 0)
	{
		new_str[size] = 0;
		size--;
	}
	concat_helper(new_str, s1);
	concat_helper(new_str, s2);
	return (new_str);
}