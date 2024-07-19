#include "philo.h"

t_philo	*ft_lstnew(int content)
{
	t_philo	*root;

	root = malloc(sizeof(t_philo));
	if (!root)
		return (NULL);
	root->id = content;
	root->next = NULL;
	return (root);
}

int	ft_lstsize(t_philo *lst)
{
	size_t	length;

	length = 0;
	while (lst)
	{
		length++;
		lst = lst->next;
	}
	return (length);
}

t_philo	*ft_lstlast(t_philo *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void ft_lstadd_back(t_philo **lst, t_philo *new)
{
    t_philo *curr;

    if (!lst || !new)
        return;
    curr = *lst;
    if (!curr)
    {
        *lst = new;
        new->prev = NULL;
        new->next = NULL;
        return;
    }
    while (curr->next)
        curr = curr->next;
    curr->next = new;
    new->prev = curr;
    new->next = NULL;
}

void	ft_lstclear(t_philo **lst, void (*del)(void*))
{
	t_philo	*curr;
	t_philo	*temp;

	curr = *lst;
	while (curr)
	{
		temp = curr->next;
		ft_lstdelone(curr, del);
		curr = temp;
	}
	*lst = NULL;
}

void	ft_lstdelone(t_philo *lst, void (*del)(void*))
{
	(void)del;
	if (del != NULL)
	{
		if (lst)
		{
			free(lst);
		}
	}
}