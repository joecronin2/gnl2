/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcronin <jcronin@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 02:02:39 by jcronin           #+#    #+#             */
/*   Updated: 2026/02/13 02:02:43 by jcronin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 16
#endif

static char	*get_line(char *stash)
{
	char	*nl;
	size_t	len;
	char	*buf;

	nl = ft_strchrnul(stash, '\n');
	len = nl - stash;
	if (*nl == '\n')
		len++;
	buf = malloc(len + 1);
	if (!buf)
		return (NULL);
	ft_strncpy(buf, stash, len);
	return (buf);
}

static char	*ft_strjoin_free(char *s1, char *s2)
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

static char	*join(char *line, char *stash)
{
	char	*newline;
	char	*nl;

	newline = get_line(stash);
	if (!newline)
		return (NULL);
	line = ft_strjoin_free(line, newline);
	if (!line)
		return (NULL);
	nl = ft_strchrnul(stash, '\n');
	if (*nl == '\n')
		nl++;
	ft_strncpy(stash, nl, BUFFER_SIZE);
	return (line);
}

static ssize_t	read_stash(int fd, char *stash)
{
	ssize_t	rd;

	rd = read(fd, stash, BUFFER_SIZE);
	if (rd > 0)
		stash[rd] = '\0';
	return (rd);
}

char	*get_next_line(int fd)
{
	static char	stash[1024][BUFFER_SIZE + 1];
	char		*line;
	char		*tmp;
	ssize_t		rd;

	line = ft_substr("", 0);
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0 || !line)
		return (free(line), NULL);
	rd = 1;
	while (rd > 0 && *ft_strchrnul(line, '\n') != '\n')
	{
		if (!*stash[fd])
			rd = read_stash(fd, stash[fd]);
		if (rd == -1)
			return (free(line), NULL);
		if (rd == 0)
			break ;
		tmp = join(line, stash[fd]);
		if (!tmp)
			return (free(line), NULL);
		line = tmp;
	}
	if (line && *line && rd != -1)
		return (line);
	return (free(line), NULL);
}

// #include <fcntl.h>
// #include <stdio.h>
//
// int	main(void)
// {
// 	char	*s;
//
// 	// int fd = open("testfile", O_RDONLY);
// 	// int fd = open("testfile", O_RDONLY);
// 	while ((s = get_next_line(0)))
// 	{
// 		// while ((s = get_next_line(fd))) {
// 		printf("line: %s", s);
// 		free(s);
// 	}
// 	// char *s = get_next_line(fd);
// 	// close(fd);
// 	return (0);
// }
