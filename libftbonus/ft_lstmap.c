#include "libft.h"

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
    t_list  *result;
    t_list  *itr;

    result = ft_lstnew(f(lst));
    itr = result;
    if (!result)
        return (result);
    lst = lst -> next;
    while (lst)
    {
        itr ->next = ft_lstnew(f(lst));
        if (!(itr -> next))
        {
            ft_lstclear(&result,*del);
            return (0);
        }
        itr = itr -> next;
        lst = lst -> next;
    }
    return (result);
}
