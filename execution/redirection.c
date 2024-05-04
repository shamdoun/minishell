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
        if (!line || !ft_strncmp(line, shell->all_input->all_files->delimeter, ft_strlen(line)))
            break ;
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);
}

void open_input_files(t_shell *shell)
{
    t_input *first_input;
    t_file *first_file;

    first_input = shell->all_input;
    first_file = NULL;
    while (shell->all_input)
    {
        if (shell->all_input->all_files)
            first_file = shell->all_input->all_files;
        while (shell->all_input->all_files)
        {
            if (shell->all_input->all_files->type >= 3 && shell->all_input->in_file)
                close(shell->all_input->in_file);
            else if (shell->all_input->all_files->type == 4)
                here_doc(shell);
            if (shell->all_input->all_files->type == 3)
                shell->all_input->in_file = open(shell->all_input->all_files->file_name, O_RDONLY, 0777);
            if (shell->all_input->in_file < 0)
                perror("failed to open file!");
            shell->all_input->all_files = shell->all_input->all_files->next;
        }
        if (first_file)
            shell->all_input->all_files = first_file;
        shell->all_input = shell->all_input->next;
    }
    shell->all_input = first_input;
}

void redirect_streams(t_shell *shell)
{
    while (shell->all_input->all_files)
    {
        if (shell->all_input->all_files->type < 3 && shell->all_input->out_file > 1)
            close(shell->all_input->out_file);
        if (shell->all_input->all_files->type == 1)
            shell->all_input->out_file = open(shell->all_input->all_files->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (shell->all_input->all_files->type == 2)
            shell->all_input->out_file = open(shell->all_input->all_files->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
        shell->all_input->all_files = shell->all_input->all_files->next;
    }
    if (shell->all_input->in_file)
        dup2(shell->all_input->in_file, STDIN_FILENO);
    if (shell->all_input->out_file > 1)
        dup2(shell->all_input->out_file, STDOUT_FILENO);
}