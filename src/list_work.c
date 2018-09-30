#include "wolf.h"

t_vector	*ft_add_new(t_vector *head)
{
	t_vector *new;

	new = (t_vector *)malloc(sizeof(t_vector));
	new->next = NULL;
	if (head)
	{
		while (head->next)
			head = head->next;
		head->next = new;
	}
	return (new);
}