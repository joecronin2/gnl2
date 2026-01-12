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

char *ft_strncpy(char *dest, const char *src, size_t size) {
  size_t i = 0;
  while (i < size && src[i]) {
    dest[i] = src[i];
    i++;
  }
  dest[i] = '\0';
  return dest;
}

size_t ft_strlen(const char *s) {
  const char *p = s;

  while (*p)
    p++;
  return (p - s);
}

char *ft_strchrnul(const char *s, int c) {
  while (*s && *s != c)
    s++;
  return ((char *)s);
}

char *ft_substr(char const *s, size_t len) {
  char *str = malloc(len + 1);
  if (!str)
    return NULL;
  ft_memcpy(str, s, len);
  str[len] = '\0';
  return str;
}

char *ft_strjoin_free(char *s1, char *s2) {
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
  free(s1);
  free(s2);
  return (b);
}

char *get_line(char *stash) {
  char *nl = ft_strchrnul(stash, '\n');
  size_t len = nl - stash;
  if (*nl == '\n')
    len++;
  char *buf = malloc(len + 1);
  if (!buf)
    return NULL;
  ft_strncpy(buf, stash, len);
  return buf;
}

void update_stash(char *stash) {
  char *nl = ft_strchrnul(stash, '\n');
  if (*nl == '\n')
    nl++;
  ft_strncpy(stash, nl, BUFFER_SIZE);
}

char *get_next_line(int fd) {
  if (fd < 0)
    return NULL;
  static char stash[BUFFER_SIZE + 1];
  char *line = ft_substr("", 0);
  ssize_t rd = 1;
  while (1) {
    if (!*stash) {
      rd = read(fd, stash, BUFFER_SIZE);
      if (rd < 0) {
        free(line);
        return NULL;
      }
      stash[rd] = '\0';
    }
    char *newline = get_line(stash);
    if (!newline) {
      free(line);
      return NULL;
    }
    line = ft_strjoin_free(line, newline);
    if (!line)
      return NULL;
    update_stash(stash);
    if (*ft_strchrnul(line, '\n') == '\n' || rd == 0)
      break;
  }
  if (*line)
    return line;
  free(line);
  return NULL;
}

// 01234567
// abc$0000x
//    3
// move 3-7
// abc00000x
//    3
// abcdefghx
//         8
// move 0-8

#include <stdio.h>
// int main() {
//   char stash[] = "abcdef\n12345\nabcdefghijklm";
//   // update_stash(stash);
//
//   char *s;
//   while ((s = g()))
//     printf("line: %s\n", s);
//
//   return 0;
// }

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
//   return 0;
// }
