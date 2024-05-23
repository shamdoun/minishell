#include "minishell.h"


void    *ft_malloc(size_t size, int flag)
{
    static  t_a_data    *all_allocated_data;
    static  t_a_data    *allocated_envs;
    void                *address;
    t_a_data            *tmp;

    if (!flag || flag == 2)
    {
        address = malloc(size);
        if (!address)
            return (NULL);
        if (!flag)
            add_a_data_to_linked_list(&all_allocated_data, address);
        else
            add_a_data_to_linked_list(&allocated_envs, address);
        return (address);
    }
    else
    {
        while (all_allocated_data)
        {
            tmp = all_allocated_data;
            all_allocated_data = all_allocated_data->next;
            free(tmp->address);
            tmp->address = NULL;
            free(tmp);
            tmp = NULL;
        }
        while (allocated_envs && allocated_envs->next)
        {
            tmp = allocated_envs;
            allocated_envs = allocated_envs->next;
            free(tmp->address);
            tmp->address = NULL;
            free(tmp);
            tmp = NULL;
        }
        return NULL;
    }
}