#include "minishell.h"


void free_allocated_data(t_a_data *list)
{
    t_a_data	*tmp;

    while (list)
    {
        tmp = list;
        list = list->next;
        free(tmp->address);
        tmp->address = NULL;
        free(tmp);
        tmp = NULL;
    }
}


void    *ft_malloc(size_t size, int flag)
{
    static  t_a_data    *garbage_collector;
    static  t_a_data    *allocated_envs;
    static  t_a_data    *important_addresses;
    void                *address;

    if (!flag || flag > 0)
    {
        address = malloc(size);
        if (!address)
            return (NULL);
        if (!flag)
            add_a_data_to_linked_list(&important_addresses, address);
        else if (flag == 1)
            add_a_data_to_linked_list(&allocated_envs, address);
        else if (flag == 2)
            add_a_data_to_linked_list(&garbage_collector, address);
        return (address);
    }
    else if (flag == -1)
		free_allocated_data(garbage_collector);
	else if (flag == -2)
		free_allocated_data(allocated_envs);
	else
		free_allocated_data(important_addresses);
	return (NULL);
}