#include "get_next_line.h"

void ft_shift(char *s, int start)
{
    int i = 0;
    while (s[start])
    {
        s[i] = s[start];
        i++;
        start++;
    }
    s[i] = '\0';
}

int ft_islign(const char *s)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] == '\n')
            return i;
        i++;
    }
    return -1;
}

size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t i = 0;
    if (dstsize > 0)
    {
        while (src[i] && i < dstsize - 1)
        {
            dst[i] = src[i];
            i++;
        }
        dst[i] = '\0';
    }
    while (src[i])
        i++;
    return i;
}

char *ft_split_f(char **s, int *eof, int fd)
{
    int i;
    char *tmp;
    char *ret;
    char buffer[BUFFER_SIZE + 1];

    i = ft_islign(*s);
    if (i >= 0)
    {
        i++;
        ret = malloc((i + 1) * sizeof(char));
        if (!ret)
            return NULL;
        ft_strlcpy(ret, *s, i + 1);
        ft_shift(*s, i);
        return ret;
    }
    else
    {
        *eof = read(fd, buffer, BUFFER_SIZE);
        if (*eof <= 0)
        {
            if (**s == '\0')
            {
                free(*s);
                *s = NULL;
                return NULL;
            }
            ret = strdup(*s);
            free(*s);
            *s = NULL;
            return ret;
        }
        buffer[*eof] = '\0';
        tmp = malloc((strlen(*s) + *eof + 1) * sizeof(char));
        if (!tmp)
            return NULL;
        strcpy(tmp, *s);
        strcat(tmp, buffer);
        free(*s);
        *s = tmp;
        return ft_split_f(s, eof, fd);
    }
}