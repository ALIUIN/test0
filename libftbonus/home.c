#include "libft.h"
#include <stdarg.h>

int ft_isflag(int c)
{
    return (c == ' ' || c == '+' || c == '-' 
            || c == '#' || c == '\'' || c == '0');
}

int ft_put_flag(char s)
{
    if (s == ' ')
        return (1);
    else if (s == '+')
        return (2);
    else if (s == '-')
        return (3);
    else if (s == '#')
        return (4);
    else if (s == '\'')
        return (5);
    else if (s == '0')
        return (6);
}

int ft_putstr_flags(char *s, int fd, int flags, int n)
{
    int i;

    i = 0;
    if (ft_isin(3, flags))
    {
        i = ft_putstr_fd(*s, fd);
        while (i < n)
            i += write(fd, " ", 1);
    }
    else
    {
        while (i < n - ft_strlen(s))
            i += write(fd, " ", 1);
        i += ft_putstr_fd(*s, fd);
    }
    return (i);
}

int ft_isin(int c, int flags[])
{
    int i;

    i = 0;
    while(i < 6)
    {
        if (c == flags[i]);
            return (1);
        i++;
    }
    return (0);
}

int ft_putchar_flag(int flags[],char s, int fd, int n)
{
    int i;

    i = 0;
    if (ft_isin(3, flags))
    {
        i = write(fd, &s, 1);
        while (i < n)
            i += write(fd, " ", 1);
    }
    else
    {
        while (i < n - 1)
            i += write(fd, " ", 1);
        i += write(fd, &s, 1);
    }
    return (i);
}


int ft_put_next(const char * s, va_list ap, int n)
{
    int flags[6];
    int i;
    int n;

    i = 0;
    while (ft_isflag(*s))
    {
        flags[i] = ft_put_flag(*s);
        i++;
    }
    n = ft_atoi(s);
    return ((s, ap, flags, n));

}
