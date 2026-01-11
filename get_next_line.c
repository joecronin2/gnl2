#include "get_next_line.h"

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void *ft_memcpy(void *dest, const void *src, size_t n) {
  size_t i;

  i = 0;
  while (i < n) {
    ((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
    i++;
  }
  return (dest);
}

size_t ft_strlen(const char *s) {
  const char *p = s;

  while (*p)
    p++;
  return (p - s);
}

char *ft_strjoin(char const *s1, char const *s2) {
  size_t s1_len;
  size_t s2_len;
  char *b;

  s1_len = ft_strlen(s1);
  s2_len = ft_strlen(s2);
  b = malloc(s1_len + s2_len + 1);
  if (!b)
    return (NULL);
  ft_memcpy(b, s1, s1_len);
  ft_memcpy(b + s1_len, s2, s2_len + 1);
  return (b);
}

char *ft_strchr(const char *s, int c) {
  while (*s && *s != (char)c)
    s++;
  if (c && !*s)
    return (0);
  return ((char *)s);
}

char *ft_substr(char const *s, unsigned int start, size_t len) {
  char *b;
  size_t maxlen;

  maxlen = ft_strlen(s);
  if (start >= maxlen) {
    b = malloc(1);
    if (b)
      *b = '\0';
    return (b);
  }
  if (start + len > maxlen)
    len = maxlen - start;
  b = malloc(len + 1);
  if (!b)
    return (NULL);
  ft_memcpy(b, s + start, len);
  b[len] = '\0';
  return (b);
}

// abcdef$abcdef

char *fill_stash(int fd, char *stash) {
  char *buf = malloc(BUFFER_SIZE + 1);
  if (!buf)
    return NULL;
  if (!stash) {
    stash = malloc(1);
    stash[0] = '\0';
  }
  ssize_t b_read = 1;
  while (!ft_strchr(stash, '\n') && b_read != 0) {
    b_read = read(fd, buf, BUFFER_SIZE);
    if (b_read == -1) {
      free(buf);
      free(stash);
      return NULL;
    }
    buf[b_read] = '\0';
    char *tmp = ft_strjoin(stash, buf);
    free(stash);
    stash = tmp;
  }
  free(buf);
  return stash;
}

char *get_line(char *stash) {
  char *nl = ft_strchr(stash, '\n');
  size_t len;
  if (!nl)
    len = ft_strlen(stash);
  else
    len = (nl - stash) + 1;
  return ft_substr(stash, 0, len);
}

char *update_stash(char *stash) {
  char *nl = ft_strchr(stash, '\n');
  if (!nl) {
    free(stash);
    return NULL;
  }
  char *new = ft_substr(stash, (nl - stash) + 1, ft_strlen(nl + 1));
  free(stash);
  return new;
}

char *get_next_line(int fd) {
  static char *stash = NULL;
  if (fd < 0 || BUFFER_SIZE <= 0)
    return NULL;
  stash = fill_stash(fd, stash);
  if (!stash)
    return NULL;
  if (!*stash) {
    free(stash);
    stash = NULL;
    return (NULL);
  }
  char *line = get_line(stash);
  stash = update_stash(stash);
  return line;
}

#include <stdio.h>
int main() {
  int fd = open("testfile", O_RDONLY);
  char *s;
  while ((s = get_next_line(fd)))
    printf("line: %s", s);

  // char *s = get_next_line(fd);
  close(fd);
  return 0;
}
