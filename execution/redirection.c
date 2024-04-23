#include "../minishell.h"

void redirect_streams(t_shell *shell)
{
    while (shell->all_input->all_files)
    {
        if (shell->all_input->all_files->type < 3 && shell->all_input->out_file > 1)
            close(shell->all_input->out_file);
        else if (shell->all_input->all_files->type >= 3 && shell->all_input->in_file)
            close(shell->all_input->in_file);        
        if (shell->all_input->all_files->type == 1)
            shell->all_input->out_file = open(shell->all_input->all_files->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        else if (shell->all_input->all_files->type == 2)
            shell->all_input->out_file = open(shell->all_input->all_files->file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
        else if (shell->all_input->all_files->type == 3)
            shell->all_input->in_file = open(shell->all_input->all_files->file_name, O_RDONLY, 0666);
        shell->all_input->all_files = shell->all_input->all_files->next;
    }
    if (shell->all_input->in_file)
        dup2(shell->all_input->in_file, STDIN_FILENO);
    if (shell->all_input->out_file > 1)
        dup2(shell->all_input->out_file, STDOUT_FILENO);
}