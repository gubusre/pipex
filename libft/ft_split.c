/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:51:36 by gubusque          #+#    #+#             */
/*   Updated: 2025/09/10 13:34:17 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **result, size_t w_idx)
{
	size_t	i;

	i = 0;
	while (i < w_idx)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

static size_t	count_w(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static char	**spliter(char **result, char const *s, char c, size_t w_count)
{
	size_t	i;
	size_t	w_idx;
	size_t	w_start;

	i = 0;
	w_idx = 0;
	while (w_idx < w_count)
	{
		while (s[i] == c && s[i])
			i++;
		w_start = i;
		while (s[i] != c && s[i])
			i++;
		result[w_idx] = ft_substr(s, (unsigned int)w_start, i - w_start);
		if (!result[w_idx])
			return (ft_free(result, w_idx));
		w_idx++;
	}
	result[w_idx] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	w_count;

	if (!s)
		return (NULL);
	w_count = count_w(s, c);
	result = (char **) malloc(sizeof(char *) * (w_count + 1));
	if (!result)
		return (NULL);
	return (spliter(result, s, c, w_count));
}
/*
#include <stdio.h>

int	main(int argc, const char *argv[])
{
	char	**tmp;
	int	i;

	if (argc != 2)
		return (0);
	tmp = ft_split(argv[1], ' ');
	i = 0;
	*tmp[3] = NULL;
	while (tmp[i])
	{
		printf("%s\n", tmp[i]);
		free(tmp[i]);
		i++;
	}
	return (0);
}
*/
