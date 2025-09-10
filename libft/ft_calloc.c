/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:33:48 by gubusque          #+#    #+#             */
/*   Updated: 2025/04/12 22:14:30 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;
	size_t			i;

	i = 0;
	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, count * size);
	return (tmp);
}
/* Desc
 *	 The calloc() function allocates memory for an 
 *	 array of nmemb (number of members) elements of size  bytes  each
 *      and  returns  a  pointer to the allocated memory.
 *      The memory is set to zero.  If nmemb or
 *      size is 0, then calloc() returns either NULL,
 *      or a unique pointer value that can later  be
 *      successfully  passed  to  free().  If the multiplication of 
 *      nmemb and size would result in
 *      integer overflow, then calloc() returns an error.
 *      By contrast, an integer overflow  would
 *      not  be  detected  in  the following call to malloc(),
 *      with the result that an incorrectly
 *      sized block of memory would be allocated:
 *         malloc(nmemb * size);
 *
 * Return
 *      The  malloc()  and  calloc()  functions return a pointer 
 *      to the allocated memory, which is
 *      suitably aligned for any built-in type.
 *      On error, these functions return NULL.  NULL  may
 *      also  be returned by a successful call to malloc() 
 *      with a size of zero, or by a successful
 *      call to calloc() with nmemb or size equal to zero.
 *
 * My_com
 * 	safe mem for element of X bytes.
 */
