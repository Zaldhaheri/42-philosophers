#include "philo.h"

t_philo	*ft_lstnew(void *content)
{
	t_philo	*root;

	root = malloc(sizeof(t_philo));
	if (!root)
		return (NULL);
	root->content = content;
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

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*curr;

	curr = *lst;
	if (!curr)
	{
		*lst = new;
		return ;
	}
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}