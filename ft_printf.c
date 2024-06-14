#include <stdio.h>
#include <stdarg.h>
#include <stdarg.h>
#include <unistd.h>
#include "libft.h"

int ft_putchar_fd(int s, int fd)
{
    return (write(fd, &s, 1));
}

int ft_putstr_fd(char *s, int fd)
{
    if (!(*s))
        return (0);
    return (ft_putchar_fd(*s, fd) + (ft_putstr_fd(s + 1, fd)));
}

void ft_toupper(char *s)
{
    while (*s)
    {
        if (*s <= 'z' && *s >= 'a' )
            *s -= 32;
        s++;
    }
}

int ft_putnbrbase_fd(long int l, int fd, int base, int capitalise)
{
    char    *symbols;

    symbols = "0123456789abcdef";
    if (capitalise)
        ft_toupper(symbols);
    if (l < 0)
    {
        write(fd, "-", 1);
        return (1 + ft_putnbrbase_fd(-l, fd, 10, capitalise));
    }
    else if (l < base)
    {
        return (ft_putchar_fd(symbols[l], fd));
    }
    return (ft_putnbrbase_fd(l / base, fd, base, capitalise) + ft_putnbrbase_fd(l % base, fd, base, capitalise));
}

int ft_putadr_fd(void *ptr, int fd)
{
    unsigned long addr = (unsigned long)ptr;
    int count = 0;

    count += ft_putstr_fd("0x", fd);

    for (int i = (sizeof(addr) * 2) - 1; i >= 0; i--)
    {
        int digit = (addr >> (i * 4)) & 0xF;
        if (digit < 10)
            count += ft_putchar_fd('0' + digit, fd);
        else
            count += ft_putchar_fd('a' + (digit - 10), fd);
    }

    return count;
}

int ft_putdec_fd(double l, int fd, int precision)
{
    int count;
    int digit;

    count = 0;
    while (precision--)
    {
        l *= 10;
        digit = (int)l % 10;
        count += ft_putchar_fd('0' + digit, fd);
    }
    return (count);
}

int ft_putnbrdouble_fd(double d, int fd)
{
    long int    l;
    int         count;

    count = 0;
    l = (long int) d;
    d = d - l;
    count += ft_putnbrbase_fd(l, fd, 10, 0);
    count += ft_putchar_fd('.', fd);
    count += ft_putdec_fd(d, fd, 6);
    return (count);
}

static int ft_countarg(const char * s)
{
    if (!(*s))
        return (0);
    if (*s == '%' && *(s + 1) == '%')
        return (1 + ft_countarg(s + 2));
    if (*s == '%')
        return (1 + ft_countarg(s + 1));
    return ft_countarg(s + 1);
}

static int ft_put(const char * s, va_list ap)
{
    if (*s == '%')
        return (ft_putchar_fd(*s, 1));
    else if (*s == 'd')
        return (ft_putnbrdouble_fd(va_arg(ap, double), 1));
    else if (*s == 'c')
        return (ft_putchar_fd(va_arg(ap, int), 1));
    else if (*s == 's')
        return (ft_putstr_fd(va_arg(ap, char *), 1));
    else if (*s == 'p')
        return (ft_putadr_fd(va_arg(ap, void *), 1));
    else if (*s == 'i')
        return (ft_putnbrbase_fd(va_arg(ap, int), 1, 10, 0));
    else if (*s == 'u')
        return (ft_putnbrdouble_fd(va_arg(ap, unsigned int), 1));
    else if (*s == 'x')
        return (ft_putnbrbase_fd(va_arg(ap, int), 1, 16, 0));
    else if (*s == 'X')
        return (ft_putnbrbase_fd(va_arg(ap, int), 1, 16 , 1));
}

int ft_printf(const char *__format, ...)
{
    va_list ap;
    const char    *s;
    int     count;

    count = 0;
    s = __format;
    va_start(ap, __format);
    while (*s)
    {
        if (*s == '%')
        {
            count += ft_put(s + 1, ap);
            s += 2;
        }
        else
        {
            count += ft_putchar_fd(*s, 1);
            s++;
        }
    }
    va_end(ap);
    return (count);
}

int main()
{
    ft_printf("Hello %s! Number: %i, Char: %c\n", "world", 123, 'A');
    ft_printf("Pointer: %p\n", (void *)main);
    ft_printf("Unsigned: %u, Hex: %x, HEX: %X\n", 123u, 0x123, 0x123);
    ft_printf("Double: %d\n", 123.456);
    return 0;
}