#include "../execution.h"

char *ft_join_args(t_arg *args)
{
    char *result;
    char *tmp;

    result = NULL;
    result = ft_strdup(args->arg);
    args = args->next;
    while (args)
    {
        tmp = ft_strjoin(" ", args->arg);
        if (!tmp)
            perror("failed to join:");
        result = ft_strjoin(result, tmp);
        args = args->next;
    }
    return (result);
}

void echo_message(t_arg *args)
{
    bool new_line;
    char *joined_args;
    char **split;

    new_line = true;
    //!!TODO:parse args
    if (!args->arg)
    {
        printf("\n");
        return ;
    }
    joined_args = ft_join_args(args);
    split = ft_split_1(joined_args, ' ');
    while (*split && !ft_strncmp(*split, "-n", ft_strlen(*split)))
    {
        split++;
        new_line = false;
    }

    while (*split)
    {
        printf("%s", *split);
        if (*(split+1))
            printf(" ");
        split++;
    }
    if (new_line)
        printf("\n");
}