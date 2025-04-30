/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:10:05 by spunyapr          #+#    #+#             */
/*   Updated: 2025/04/30 16:03:46 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int main_execution(t_token *tree)
{
    int exit_status;
    
    // Build a tree start from root
    if (!tree)
        return (0);
    if (tree->type == PIPE)
        exit_status = pipe_process(tree); // TODO 
    else if (tree->type == CMD)
        exit_status = simple_command_process(tree); // TODO
    else
        return (handle_unexpected_type(tree)); // TODO
}

int pipe_process(t_token *token)
{
    if (!token)
        return (0);
    
}


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

