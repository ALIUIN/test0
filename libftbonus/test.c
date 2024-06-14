/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <string.h>  // Include for strdup
#include <stdlib.h>


typedef struct s_list
{
    void            *content;
    struct s_list   *next;
}                   t_list;


t_list *ft_lstnew(void *content)
{
    t_list  *lst;

    lst = malloc(sizeof(t_list));
    if (!lst)
        return (lst);
    lst->content = content;
    return (lst);
}

int ft_lstsize(t_list *lst)
{
    if (!lst)
        return (0);
    return (1 + ft_lstsize(lst->next));
}

t_list *ft_lstlast(t_list *lst)
{
    while (lst -> next)
    {
        lst = lst -> next;
    }
    return (lst);
}

void ft_lstiter(t_list *lst, void (*f)(void *))
{
    while (lst)
    {
        f(lst->content);
        lst = lst ->next;
    }
}

void ft_lstdelone(t_list *lst, void (*del)(void *))
{
    del(lst -> content);
}

void ft_lstclear(t_list **lst, void (*del)(void *))
{
    t_list *current;
    t_list *next;

    if (!lst || !*lst || !del)
        return;

    current = *lst;
    while (current)
    {
        next = current->next;
        ft_lstdelone(current, del);
        current = next;
    }
    *lst = NULL;
}

void ft_lstadd_front(t_list **lst, t_list *new)
{
    new->next = (*lst)->next;
    *lst = new;
}

void ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list  *nlst;

    if (!(*lst))
        *lst = new;
    nlst = ft_lstlast(*lst);
    nlst -> next = new;    
}

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
    t_list  *result;
    t_list  *itr;

    result = ft_lstnew((unsigned char *)f(lst));
    itr = result;
    if (!result)
        return (result);
    lst = lst -> next;
    while (lst)
    {
        itr ->next = ft_lstnew((unsigned char *)f(lst));
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


void print_content(void *content)
{
    printf("%s\n", (char *)content);
}

void delete_content(void *content)
{
    free(content);
}

void *duplicate_content(void *content)
{
    char *new_content = strdup((char *)content);
    return "q";
}

int main()
{
    // Create new list nodes
    t_list *node1 = ft_lstnew(strdup("Node 1"));
    t_list *node2 = ft_lstnew(strdup("Node 2"));
    t_list *node3 = ft_lstnew(strdup("Node 3"));

    // Add nodes to the list
    ft_lstadd_back(&node1, node2);
    ft_lstadd_back(&node1, node3);

    // Print list size
    printf("List size: %d\n", ft_lstsize(node1));
    // Iterate and print list content
    printf("List contents:\n");
    ft_lstiter(node1, print_content);

    // Map list to a new list with duplicated content
    t_list *new_list = ft_lstmap(node1, duplicate_content, delete_content);
    
    // Iterate and print new list content
    printf("New list contents:\n");
    ft_lstiter(new_list, print_content);

    // Clear both lists
    ft_lstclear(&node1, delete_content);
    ft_lstclear(&new_list, delete_content);
    return 0;
}
