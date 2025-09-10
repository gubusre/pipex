/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:17:46 by gubusque          #+#    #+#             */
/*   Updated: 2025/04/09 23:11:12 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	if (dst == (void *)0 && src == (void *)0)
		return (dst);
	tmp_dst = (unsigned char *) dst;
	tmp_src = (unsigned char *) src;
	while (len-- > 0)
		*(tmp_dst++) = *(tmp_src++);
	return (dst);
}
/*
 * DESCRIPTION
 * 	The memcpy() function copies n bytes 
 * 	from memory area src to memory area dest.
 * 	The memory areas must not overlap.
 * 	Use memmove(3) if the memory areas do overlap.
 * RETURN VALUE
 * The memcpy() function returns a pointer to dest.
 */
