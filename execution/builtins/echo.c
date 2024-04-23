#include "../execution.h"

void echo_message(char *args)
{
    bool new_line;

    new_line = true;
    //!!TODO:parse args
    char **split = ft_split(args, ' ');
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