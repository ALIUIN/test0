#include "libft.h"

void ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list  *nlst;

    if (!(*lst))
        *lst = new;
    nlst = ft_lstlast(*lst);
    nlst -> next = new;    
}
