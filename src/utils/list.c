#include "grim_fetcher.h"

t_list	*list_new(void *data)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->prev = 0;
	new->next = 0;
	new->data = data;
	return (new);
}

void	list_add_front(t_list **list, t_list *new)
{
	if (!new)
		return ;
	new->prev = 0;
	new->next = *list;
	if (*list)
		(*list)->prev = new;
	*list = new;
	return ;
}

void	list_del_one(t_list **list, void (*del)(void *))
{
	t_list	*prev;
	t_list	*next;

	if (!*list)
		return ;
	prev = (*list)->prev;
	next = (*list)->next;
	if (del)
		del((*list)->data);
	free(*list);
	*list = next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	return ;
}

int	list_add_sorted(t_list **list, t_list *new, int (*f)(void *, void *))
{
	t_list	*curr;

	if (!new || !f)
		return (0);
	if (!*list || f((*list)->data, new->data) > 0)
	{
		list_add_front(list, new);
		return (1);
	}
	curr = *list;
	while (curr->next && f(curr->next->data, new->data) <= 0)
		curr = curr->next;
	new->prev = curr;
	new->next = curr->next;
	if (curr->next)
		curr->next->prev = new;
	curr->next = new;
	return (1);
}

void	list_clear(t_list **list, void (*del)(void *))
{
	while (list && *list)
		list_del_one(list, del);
	return ;
}
