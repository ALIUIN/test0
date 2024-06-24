#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 32
#endif

char *get_next_line(int fd);
void ft_shift(char *s, int start);
int ft_islign(const char *s);
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);
char *ft_split_f(char **s, int *eof, int fd);

#endif
