#include "../minishell.h"

extern volatile sig_atomic_t stop_signal;

void handle_signal_heredoc()
{
    close(STDIN_FILENO);
    // write(1, "\n", 1);
    stop_signal = 1;
}

int here_doc(t_input *input, t_file *file)
{
    char *line;
    int fd = open("here_doc.txt", O_CREAT | O_TRUNC | O_WRONLY, 0777);
    if (fd < 0)
        perror("failed to open here_doc file for writing");
    input->here_doc = open("here_doc.txt", O_RDONLY, 0777);
    if (input->here_doc < 0)
        perror("failed to open here_doc file!");
    unlink("here_doc.txt");
    signal(SIGINT, &handle_signal_heredoc);
    while (1)
    {
        line = readline(">");
        if (!line || !ft_strncmp(line, file->delimeter, ft_strlen(line) + 1))
            break ;
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);
    if (stop_signal == 1)
        return (1);
    if (!line)
        stop_signal = 2;
    return (0);
}

int open_here_docs(t_shell *shell)
{
    t_input *i_head;
    t_file *f_head;


    i_head = shell->all_input;
    while (i_head)
    {
        f_head = i_head->all_files;
        while (f_head)
        {
            if (f_head->type == 4)
            {
                if (i_head->here_doc)
                    close(i_head->here_doc);
                if (here_doc(i_head, f_head))
                    return (1);
            }
            f_head = f_head->next;
        }
        i_head = i_head->next;
    }
    return (0);
}

int open_input_files(t_shell *shell)
{
    t_file *first_file;

    first_file = NULL;
    while (shell->all_input->all_files)
    {
        if (shell->all_input->all_files->type >= 3 && shell->all_input->in_file)
            close(shell->all_input->in_file);
        if (shell->all_input->all_files->type == 3)
            shell->all_input->in_file = open(shell->all_input->all_files->file_name, O_RDONLY, 0777);
        if (shell->all_input->all_files->type == 4)
            shell->all_input->in_file = shell->all_input->here_doc;
        if (shell->all_input->in_file < 0)
        {
            perror("bash: ");
            return (1);
        }
        shell->all_input->all_files = shell->all_input->all_files->next;
    }
    if (first_file)
        shell->all_input->all_files = first_file;
    return (0);
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
    if (shell->all_input->here_doc)
        close(shell->all_input->here_doc);
}