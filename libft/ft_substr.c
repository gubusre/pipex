/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:02:06 by gubusque          #+#    #+#             */
/*   Updated: 2025/04/09 23:08:14 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ss;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	ss = (char *) ft_calloc(len + 1, (sizeof(char)));
	if (!ss)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ss[i] = s[start + i];
		i++;
	}
	return (ss);
}
/* Return 
 * 	NULL when parameter sent is invalid or mem alloc is not possible, 
 * 	if mem alloc is possible always return what is expected, 
 * 	even if it's something empty.
 */
