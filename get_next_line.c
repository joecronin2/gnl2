/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcronin <jcronin@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:17:12 by jcronin           #+#    #+#             */
/*   Updated: 2026/01/12 18:20:14 by jcronin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_utils.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 16
#endif

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
	}
	ft_memcpy(b, s1, s1_len);
	ft_memcpy(b + s1_len, s2, s2_len + 1);
	free(s1);
	free(s2);
	return (b);
}

char	*get_line(char *stash)
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

void	update_stash(char *stash)
{
	char	*nl;

	nl = ft_strchrnul(stash, '\n');
	if (*nl == '\n')
		nl++;
	ft_strncpy(stash, nl, BUFFER_SIZE);
}

char	*join(char *line, char *stash)
{
	char	*newline;

	newline = get_line(stash);
	if (!newline)
		return (NULL);
	line = ft_strjoin_free(line, newline);
	update_stash(stash);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	stash[1024][BUFFER_SIZE + 1];
	char		*line;
	ssize_t		rd;

	if (fd < 0)
		return (NULL);
	line = ft_substr("", 0);
	rd = 1;
	while (1)
	{
		if (!*stash[fd])
		{
			rd = read(fd, stash[fd], BUFFER_SIZE);
			if (rd < 0)
				return (free(line), NULL);
			stash[fd][rd] = '\0';
		}
		line = join(line, stash[fd]);
		if (*ft_strchrnul(line, '\n') == '\n' || rd == 0)
			break ;
	}
	if (*line)
		return (line);
	free(line);
	return (NULL);
}

// #include <stdio.h>
// #include <fcntl.h>
// int main() {
//   int fd = open("testfile", O_RDONLY);
//   // int fd = open("testfile", O_RDONLY);
//   char *s;
//   // while ((s = get_next_line(0)))
//   while ((s = get_next_line(fd))) {
//     printf("line: %s", s);
//     free(s);
//   }
//
//   // char *s = get_next_line(fd);
//   // close(fd);
//   return (0);
// }
