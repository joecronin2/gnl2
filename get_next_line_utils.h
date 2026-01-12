/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcronin <jcronin@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 21:12:19 by jcronin           #+#    #+#             */
/*   Updated: 2026/01/10 21:12:20 by jcronin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strncpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strchrnul(const char *s, int c);
char	*ft_substr(char const *s, size_t len);
