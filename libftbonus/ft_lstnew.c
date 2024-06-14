#include "libft.h"

t_list *ft_lstnew(void *content)
{
    t_list  *lst;

    lst = malloc(sizeof(t_list));
    if (!lst)
        return (lst);
    lst->content = content;
    return (lst);
}