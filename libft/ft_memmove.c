/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwong <cwong@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:04:40 by cwong             #+#    #+#             */
/*   Updated: 2025/04/22 11:46:06 by cwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_ptr;
	const unsigned char	*src_ptr;
	size_t				i;

	dest_ptr = (unsigned char *) dest;
	src_ptr = (const unsigned char *) src;
	if (dest_ptr == src_ptr || n == 0)
		return (dest);
	if (dest_ptr > src_ptr && dest_ptr < src_ptr + n)
	{
		i = n;
		while (i-- > 0)
			dest_ptr[i] = src_ptr[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			dest_ptr[i] = src_ptr[i];
			i++;
		}
	}
	return (dest);
}
