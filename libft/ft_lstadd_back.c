#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*s;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	s = ft_lstlast(*lst);
	s->next = new;
}
