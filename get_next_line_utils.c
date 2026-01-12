/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcronin <jcronin@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 21:12:22 by jcronin           #+#    #+#             */
/*   Updated: 2026/01/10 21:12:35 by jcronin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_utils.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

char	*ft_strncpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	const char	*p = s;

	while (*p)
		p++;
	return (p - s);
}

char	*ft_strchrnul(const char *s, int c)
{
	while (*s && *s != c)
		s++;
	return ((char *)s);
}

char	*ft_substr(char const *s, size_t len)
{
	char	*str;

	str = malloc(len + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s, len);
	str[len] = '\0';
	return (str);
}
