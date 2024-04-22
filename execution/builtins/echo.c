#include "../execution.h"

void echo_message(char **args)
{
    //!!TODO:parse args
    if (args[1])
        printf("%s", args[1]);
    else
        printf("%s\n", args[0]);
}