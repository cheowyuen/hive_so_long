/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheowyuenwong <cheowyuenwong@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:26:23 by cwong             #+#    #+#             */
/*   Updated: 2025/04/25 21:04:07 by cheowyuenwo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	int	length;

	length = 0;
	while (s[length])
		length++;
	while (length >= 0)
	{
		if (s[length] == (char) c)
			return ((char *)(s + length));
		length--;
	}
	return (NULL);
}
