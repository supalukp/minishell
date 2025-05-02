/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:10:05 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/02 15:20:35 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	main_execution(t_token *tree, char **env)
{
	int	exit_status;

	exit_status = 0;
	// Build a tree start from root
	if (!tree)
		return (0);
	if (tree->type == PIPE)
		exit_status = pipe_process(tree, env); // TODO
	else if (tree->type == CMD)
    {
        // if (is_buildin(tree->name) == true)
        //     exit_status = exec_buildin();
		exit_status = simple_command_process(tree, env); // TODO
    }
	// else
	//     return (handle_unexpected_type(tree)); // TODO
	return (exit_status);
}

char	*find_executable(char **all_path, char *command)
{
	int		j;
	char	*add_slash;
	char	*path_command;

	j = 0;
	while (all_path[j] != NULL)
	{
		add_slash = ft_strjoin(all_path[j], "/");
		if (!add_slash)
			return (free_matrix(all_path), NULL);
		path_command = ft_strjoin(add_slash, command);
		if (!path_command)
			return (free_matrix(all_path), NULL);
		free(add_slash);
		if (access(path_command, F_OK | X_OK) == 0)
		{
			free_matrix(all_path);
			return (ft_strdup(path_command));
		}
		free(path_command);
		j++;
	}
	return (free_matrix(all_path), NULL);
}

char	*get_path(char *command, char **envp)
{
	int		i;
	char	**all_path;

	i = 0;
	if (!command || !envp)
		return (NULL);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			all_path = ft_split(ft_strchr(envp[i], '=') + 1, ':');
			if (!all_path)
				return (NULL);
			return (find_executable(all_path, command));
		}
		i++;
	}
	return (NULL);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}

// int simple_command_process(t_token *tree, char **env)
// {
//     int exit_status;
//     char **args;
//     char *paths;

//     args = ft_split(tree->name, ' ');
//     // if (!args)
//     //     exit_close_fd();
//     paths = get_path(args[0], env);
//     // if (!paths)
//     //     exit_close_fd();

//     // Check if there is REDIRECT
//     // if (tree->   ->type == INFILE || )
//     //     set_up_redirect();

//     execve(paths, args, NULL);
//     free_matrix(args);
//     //exit_error();
// }

int	simple_command_process(t_token *tree, char **env)
{
	pid_t	pid;
	int		exit_status;
	char	**args;
	char	*paths;

	args = ft_split(tree->name, ' ');
	if (!args)
		return (1);
	paths = get_path(args[0], env);
	if (!paths)
	{
		free_matrix(args);
		return (127);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		free_matrix(args);
		free(paths);
		return (1);
	}
	if (pid == 0)
	{
		execve(paths, args, env);
		perror("execve failed");
		free_matrix(args);
		free(paths);
		exit(1);
	}
	else
	{
		waitpid(pid, &exit_status, 0);
		free_matrix(args);
		free(paths);
		if (WIFEXITED(exit_status))
			return (WEXITSTATUS(exit_status));
		else
			return (1);
	}
}

int	pipe_process(t_token *tree, char **env)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		exit_status;

	exit_status = 0;
	if (pipe(pipefd) == -1)
		return (perror("pipe failed"), EXIT_FAILURE);
	pid1 = fork();
	if (pid1 == -1)
		return (perror("fork failed"), EXIT_FAILURE);
	if (pid1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exit(main_execution(tree->left, env));
	}
	pid2 = fork();
	if (pid2 == -1)
		return (perror("fork"), EXIT_FAILURE);
	if (pid2 == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exit(main_execution(tree->right, env));
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &exit_status, 0);
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (EXIT_FAILURE);
}

	// else if (WIFSIGNALED(exit_status))
		//     return (128 + WTERMSIG(exit_status));
// void execute_buidin(t_branch *branch);
// void each_branch_execute(t_branch *branch);
// void execute_external(t_branch *branch);

// void main_execution(t_program *prog)
// {
//     t_branch *branch;

//     branch = prog->first_branch;
//     while (branch)
//     {
//         each_branch_execute(branch);
//         branch = branch->next;
//     }
// }

// void each_branch_execute(t_branch *branch)
// {
//     // Create pipe

//     // Handle Redirection

//     // Check if it's build in
//     if (is_buildin(branch->first_token))
//     {
//         execute_buildin(branch);
//     }
//     else
//     {
//         execute_external(branch);
//     }
// }

// void execute_buidin(t_branch *branch)
// {
//     char *cmd;
//     int exit_status;

//     exit_status = 1;
//     cmd = branch->first_token;
//     if (!ft_strcmp(cmd, "echo"))
//         exit_status = ft_echo();
//     else if (!ft_strcmp(cmd, "cd"))
//         exit_status = ft_cd();
//     else if (!ft_strcmp(cmd, "pwd"))
//         exit_status = ft_pwd();
//     else if (!ft_strcmp(cmd, "export"))
//         exit_status = ft_export();
//     else if (!ft_strcmp(cmd, "unset"))
//         exit_status = ft_unset();
//     else if (!ft_strcmp(cmd, "export"))
//         exit_status = ft_export();
//     else if (!ft_strcmp(cmd, "unset"))
//         exit_status = ft_unset();
//     else if (!ft_strcmp(cmd, "env"))
//         exit_status = ft_env();
//     else if (!ft_strcmp(cmd, "exit"))
//         exit_status = ft_exit();
//     return (exit_status);
// }

// void execute_external(t_branch *branch)
// {
//     /*
//         // Fork

//         // In child process
//         if (pid == 0)
//         {
//             //Child Process
//             execve();
//         }
//         else
//         {
//             //Parent Process
//             waitpid(); // Wait child
//         }
//     */
// }
