#include "../execution.h"

// char *ft_getenv(char *name, char **env)
// {
//     char **split;
//     char *found;

//     while (*env)
//     {
//         split = ft_split(*env, '=');
//         if (!ft_strncmp(split[0], name, ft_strlen(name) + 1))
//         {
//             found = ft_strdup(split[1]);
//             free_array(split);
//             return (found);
//         }
//         free_array(split);
//         env++;
//     }
//     return (NULL);
// }


// void change_directory(char *path, t_status **s_list, char ***env)
// {
//     int return_value;

//     return_value = 0;
//     if (path && ft_strncmp(path, "~", 2))
//         return_value = chdir(path);
//     else
//     {
//         path = ft_getenv("HOME", *env);
//         if (path)
//             return_value = chdir(path);
//         ft_lstadd_allocated_data_back(&(*s_list)->all_a_data, ft_lstnew_a_data(path));
//     }
//     if (return_value)
//     {
//         ft_lstadd_back(s_list, ft_lstnew(errno));
//         perror("cd");
//     }
// }

// int env_exists(char *name, char **env)
// {
//     char **split;
//     while (*env)
//     {
//         split = ft_split(*env, '=');
//         if (!ft_strncmp(split[0], name, ft_strlen(name) + 1))
//         {
//             free_array(split);
//             return (1);
//         }
//         free_array(split);
//         env++;
//     }
//     return (0);
// }

// void update_env(char *env_name, t_status **s_list, char *data, char ***env)
// {
//     char **new_environ;
//     new_environ = malloc(sizeof(char *) * (list_len(*env) + 1));
//     if (new_environ)
//     {
//         copy_list_updating(env_name, s_list, data, new_environ, env);
//         ft_lstadd_allocated_data_back(&(*s_list)->all_a_data, ft_lstnew_a_data(new_environ));
//         *env = new_environ;
//     }
//     else
//         ft_lstadd_back(s_list, ft_lstnew(errno));
// }

// void add_env(char *data, t_status **s_list, char ***env)
// {
//     char **new_environ;
//     char *new_data;

//     new_environ = malloc(sizeof(char *) * (list_len(*env) + 2));
//     if (new_environ)
//     {
//         ft_memcpy(new_environ, *env, list_len(*env) * sizeof(char *));
//         new_data = ft_strdup(data);
//         new_environ[list_len(*env)] = new_data;
//         new_environ[list_len(*env) + 1] = NULL;
//         *env = new_environ;
//         ft_lstadd_allocated_data_back(&(*s_list)->all_a_data, ft_lstnew_a_data(new_data));
//         ft_lstadd_allocated_data_back(&(*s_list)->all_a_data, ft_lstnew_a_data(new_environ));
//     }
//     else
//         ft_lstadd_back(s_list, ft_lstnew(errno));
// }

// void add_update_env(char *data, t_status **s_list, char ***env)
// {
//     char **split_env = ft_split(data, '=');
//     if (env_exists(split_env[0], *env))
//         update_env(split_env[0], s_list, data, env);
//     else
//         add_env(data, s_list, env);
//     free_array(split_env);
// }

// void remove_env(char *data, t_status **s_list, char ***env)
// {
//     char **new_environ = malloc(sizeof(char *) * (list_len(*env)));
//     if (new_environ)
//     {
//         copy_list_excluding(new_environ, *env, data);
//         ft_lstadd_allocated_data_back(&(*s_list)->all_a_data, ft_lstnew_a_data(new_environ));
//         *env = new_environ;             
//     }
//     else
//         ft_lstadd_back(s_list, ft_lstnew(errno)); 
// }

// void print_all_env_vars(char **env)
// {
//     int i;

//     i = 0;
//     while (env[i])
//     {
//         printf("%s\n", env[i]);
//         i++;
//     }
// }

// void exit_shell(t_command *command, char *status, t_status *s_list)
// {
//     int value;
//     (void)s_list;
//     (void)command;
//     //!!TODO: check if status is not bigger than INT_MAX
//     // free(command->input);
//     if (status)
//     {
//         value = ft_atoi(status);
//         exit(value);
//     }
//     else
//         exit(ft_lstlast(s_list)->status);
// }

void execute_binary(char **args_list, t_status **s_list, char ***env)
{
    char *cmd_path;
    pid_t child;
    
    cmd_path = find_command_path(args_list[0]);
    if (cmd_path)
    {
        child = fork();
        if (child == 0)
        {
            int rv;
            rv = execve(cmd_path, args_list, *env);
            fprintf(stderr, "error of %d\n", errno);
            if (rv)
                ft_lstadd_back(s_list, ft_lstnew(errno));
        }
        waitpid(-1, NULL, 0);
        free(cmd_path);
    }
    else
    {
        ft_lstadd_back(s_list, ft_lstnew(127));
        printf("command not found: %s\n", args_list[0]);
    }
}