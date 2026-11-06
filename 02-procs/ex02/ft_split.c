/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_split.c                                        :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: bscurtu <bscurtu@student.42malaga.com>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/09/22 11:16:04 by bscurtu          #+#    #+#              */
/*   Updated: 2026/09/22 11:21:03 by bscurtu         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static int	count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static void	free_split(char **split, int i)
{
	while (i > 0)
	{
		i--;
		free(split[i]);
	}
	free(split);
}

static char	*allocate_word(char const *s, char c)
{
	char	*word;
	int		len;
	int		i;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	*helper(char const *s, int *words, char ***split, char c)
{
	if (!s)
		return (NULL);
	*words = count_words(s, c);
	*split = malloc(sizeof(char *) * (*words + 1));
	if (!split)
		return (NULL);
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		words;
	int		i;

	if (helper(s, &words, &split, c) == NULL)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s == c)
			s++;
		split[i] = allocate_word(s, c);
		if (!split[i])
		{
			free_split(split, i);
			return (NULL);
		}
		while (*s && *s != c)
			s++;
		i++;
	}
	split[i] = NULL;
	return (split);
}