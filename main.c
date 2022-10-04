/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 10:01:32 by ssar              #+#    #+#             */
/*   Updated: 2021/06/13 20:52:57 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	launch_exec(t_pipex *all, char **envp, char **cmd)
{
	if (cmd[0][0] == '/' || cmd[0][0] == '.')
	{
		if (execve(cmd[0], cmd, envp) == -1)
			ft_error(all, strerror(errno));
	}
	else
		launch_exec_cmd_path(all, cmd[0], cmd, envp);
}

void	continue_parent(t_pipex *all, int *tube, char **envp, int pid)
{
	int	status;

	close(tube[0]);
	if (dup2(tube[1], 1) < 0)
		ft_error(all, strerror(errno));
	redir_in(all);
	launch_exec(all, envp, all->cmd1);
	close(1);
	waitpid(pid, &status, 0);
}

void	execute(t_pipex *all, char **envp)
{
	pid_t	pid;
	int		tube[2];
	int		status;

	pipe(tube);
	pid = fork();
	if (pid == -1)
		ft_error(all, strerror(errno));
	if (pid == 0)
	{	
		close(tube[1]);
		if (dup2(tube[0], 0) < 0)
			ft_error(all, strerror(errno));
		redir_out(all);
		launch_exec(all, envp, all->cmd2);
		close(tube[0]);
	}
	else
		continue_parent(all, tube, envp, pid);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*all;
	int		i;

	if (argc > 5)
	{
		write(1, "Wrong number of arguments\n", 26);
		return (1);
	}
	all = malloc(sizeof(t_pipex));
	if (!all)
	{
		write(2, strerror(errno), ft_len(strerror(errno)));
		exit(1);
	}
	i = 0;
	while (i < 4)
	{	
		all->alloc[i] = 0;
		i++;
	}
	all = get_arguments(all, argv);
	execute(all, envp);
	my_exit(all, 0);
}
