/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcronin <jcronin@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:53:35 by jcronin           #+#    #+#             */
/*   Updated: 2026/01/11 15:53:35 by jcronin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "get_next_line_utils.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*b;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	b = malloc(s1_len + s2_len + 1);
	if (!b)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	ft_memcpy(b, s1, s1_len);
	ft_memcpy(b + s1_len, s2, s2_len + 1);
	free(s1);
	free(s2);
	return (b);
}
