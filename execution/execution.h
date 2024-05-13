/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:10:12 by shamdoun          #+#    #+#             */
/*   Updated: 2024/05/13 21:40:15 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "../minishell.h"

void	execute_other_commands(t_shell *shell, int mode);
void	print_all_env_vars(char **env);
void	echo_message(t_arg *args);
void	change_directory(t_arg *path, t_shell *shell, char ***env);
char	*find_command_path(char *s, t_shell *shell);
void	copy_list_updating(char *env_name, char *data,
			t_shell *shell, char **new_environ);
int		list_len(char **list);
void	redirect_streams(t_shell *shell);
void	pipex(t_shell *shell, int mode);
void	run_built_ins(t_shell *shell, int mode);
int		open_input_files(t_shell *shell);
char	*ft_join_args(t_arg *args);
void	declare_all_envs(char **env);
void	close_unused_here_docs(t_input *input);
void	duplicate_ends(t_shell *shell, int *ends, int pipe_count, int i);
void	close_ends_and_wait(int pipe_count, int *ends, int *processes);
int		check_path(t_arg *path, char *cwd);
int		split_values(char ***split_cwd, char ***split_path,
			char *cwd, t_arg *path);
int		copy_common_path(char **joined,
			char **split_cwd, int n, char *delimeter);
void	copy_unique_path(char **joined, char **split_cwd,
			char **split_path, int i);
void	handle_signal_for_bin(int sig);
void	handle_quit_signal(int sig);
#endif