/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcronin <jcronin@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 02:00:46 by jcronin           #+#    #+#             */
/*   Updated: 2026/02/13 02:02:10 by jcronin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdlib.h>

char	*get_next_line(int fd);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strncpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strchrnul(const char *s, int c);
char	*ft_substr(char const *s, size_t len);
