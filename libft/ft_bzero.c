/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:43:36 by gubusque          #+#    #+#             */
/*   Updated: 2025/04/09 23:12:49 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t len)
{
	unsigned char	*tmp_ptr;

	tmp_ptr = (unsigned char *) s;
	while (len-- > 0)
		*(tmp_ptr++) = 0;
}
/*
 * DESCRIPTION
 *      The bzero() function erases the data in the n bytes 
 *      of the memory starting at the location
 *      pointed to by s, by writing zeros (bytes containing '\0') 
 *      to that area.
 *
 * RETURN VALUE
       None.
 */
