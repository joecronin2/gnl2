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
#include "get_next_line_utils_bonus.h"
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

static void	update_stash(char *stash)
{
	char	*nl;

	nl = ft_strchrnul(stash, '\n');
	if (*nl == '\n')
		nl++;
	ft_strncpy(stash, nl, BUFFER_SIZE);
}

static char	*join(char *line, char *stash)
{
	char	*newline;

	newline = get_line(stash);
	if (!newline)
		return (NULL);
	line = ft_strjoin_free(line, newline);
	if (!line)
		return (NULL);
	update_stash(stash);
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
	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (NULL);
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
