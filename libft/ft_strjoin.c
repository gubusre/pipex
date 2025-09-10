/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:05:22 by gubusque          #+#    #+#             */
/*   Updated: 2025/04/15 16:10:23 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	res = (char *) malloc((len1 + len2 + 1) * sizeof(char));
	if (!res)
		return (NULL);
	if (s1)
		ft_memcpy(res, s1, len1);
	if (s2)
		ft_memcpy(res + len1, s2, len2);
	res[len1 + len2] = '\0';
	return (res);
}
/*
 * Desc
 * 	Create a new string with the length of s1 + s2
 * 	and copy them there (joining);
 *
 * Return
 * 	The resultant string after copy.
 */
