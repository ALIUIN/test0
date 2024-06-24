#include "get_next_line.h"
#include <stdio.h> // For printf

char *get_next_line(int fd)
{
    static char *s = NULL;
    int eof;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    if (!s)
    {
        s = malloc((BUFFER_SIZE + 1) * sizeof(char));
        if (!s)
            return NULL;
        eof = read(fd, s, BUFFER_SIZE);
        if (eof <= 0)
        {
            free(s);
            s = NULL;
            return NULL;
        }
        s[eof] = '\0';
    }

    return ft_split_f(&s, &eof, fd);
}
