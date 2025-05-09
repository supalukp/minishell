/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:06:42 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/09 15:20:12 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    Pipe Process
    
    Init pipe
    1. Check tree type 'PIPE' (next is the left) && cmd -> redirect == NULL
    2. Count the pipes
    3. Store list of cmd (add_front tree->right)
    4. Create **fd (malloc (int *) * pipe_count + 1)
    5. Create pid (malloc (pid_t) * pipe_count)
    6. Create pipe 
        while (i < pipe_count)
        {
            if (pipe(fd[i]) == -1)
                perror("Failed create pipe");
        }
    7. Loop to fork
        while (i < pipe_count)
        {
            pid[i] = fork();
            if (pid[i] == -1)
                return (perror("Fork Failed"), EXIT_FAILURE);
            if (pid[i] == 0)
                process_child(i, );
        }
    8. Loop close all fd and waitpid
*/


int pipe_multi_process()
{
    /* 
    1. Loop check left to go to the first cmd that should execute first && Create pipes

    2. Fork process on first pipes

    3.   Child 1 = Left cmd 
        3.1 go through infile list / outfiles list (Open + Redirect)
        3.2 Execve
    
    4. Wait and get exit_status of the right one
    */
}


