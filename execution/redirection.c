#include "../minishell.h"

void here_doc(t_shell *shell)
{
    char *line;

    int fd = open("here_doc.txt", O_CREAT | O_TRUNC | O_WRONLY, 0777);
    if (fd < 0)
        perror("failed to open here_doc file for writing");
    shell->all_input->in_file = open("here_doc.txt", O_RDONLY, 0777);
    if (shell->all_input->in_file < 0)
        perror("failed to open here_doc file!");
    unlink("here_doc.txt");
    while (1)
    {
        line = readline(">");
        if (!ft_strncmp(line, shell->all_input->all_files->delimeter, ft_strlen(line)))
            break;
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);
}

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
        else
            here_doc(shell);
        shell->all_input->all_files = shell->all_input->all_files->next;
    }
    if (shell->all_input->in_file)
        dup2(shell->all_input->in_file, STDIN_FILENO);
    if (shell->all_input->out_file > 1)
        dup2(shell->all_input->out_file, STDOUT_FILENO);
}