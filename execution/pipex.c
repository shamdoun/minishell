#include "execution.h"


void create_pipes(int **ends, int count)
{
    int i;
    
    *ends = malloc(sizeof(int) * 2 * count);
    i = 0;
    while (i < count)
    {
        pipe((*ends) + 2 * i);
        i++;
    }
}

int count_nbr_of_pipes(t_input *list)
{
    int i;

    i = 0;
    while (list)
    {
        list = list->next;
        i++;
    }
    return (i - 1);
}

void pipex(t_shell *shell, int mode)
{
    pid_t child1;
    int *ends;
    int pipe_count;
    int *processes;
    pipe_count = count_nbr_of_pipes(shell->all_input);
    create_pipes(&ends, pipe_count);
    int i = 0;
    processes = malloc(sizeof(int) * (pipe_count + 1));
    while (i < pipe_count + 1)
    {
        child1 = fork();
        if (!child1)
        {
            if (i)
                dup2(ends[2 * i - 2], STDIN_FILENO);
            if (i != pipe_count)
                dup2(ends[2 * i + 1], STDOUT_FILENO);
            int j = 0;
            while (j < pipe_count * 2)
            {
                close(ends[j]);
                j++;
            }
            run_built_ins(shell, mode);
        }
        processes[i] = child1;
        close(shell->all_input->in_file);
        shell->all_input = shell->all_input->next;
        i++;
    }
    int j = 0;
    while (j < pipe_count * 2)
    {
        close(ends[j]);
        j++;
    }
    j = 0;
    while (j < pipe_count + 1)
    {
        waitpid(processes[j], NULL, 0);
        j++;
    }
    
}