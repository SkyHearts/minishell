/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:35:43 by jyim              #+#    #+#             */
/*   Updated: 2022/11/07 13:37:06 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*temp_s;
	unsigned int	i;
	unsigned char	temp_c;

	i = 0;
	temp_c = (unsigned char) c;
	temp_s = (unsigned char *) s;
	while (n > 0)
	{
		if (*temp_s != temp_c)
		{
			temp_s++;
			n--;
		}
		else
			return (temp_s);
	}
	return (NULL);
}
