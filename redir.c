/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 20:19:09 by ssar              #+#    #+#             */
/*   Updated: 2021/06/13 21:03:13 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redir_in(t_pipex *all)
{
	int			fd_file;

	fd_file = open(all->infile, O_RDONLY, 00664);
	if (fd_file == -1)
		ft_error(all, strerror(errno));
	if (dup2(fd_file, 0) < 0)
		ft_error(all, strerror(errno));
}

void	redir_out(t_pipex *all)
{
	int			fd_file;

	fd_file = open(all->outfile, O_CREAT | O_RDWR | O_TRUNC, 00664);
	if (fd_file == -1)
		ft_error(all, strerror(errno));
	if (dup2(fd_file, 1) < 0)
		ft_error(all, strerror(errno));
}

t_pipex	*get_arguments(t_pipex *all, char **str)
{
	all->infile = ft_copy(all, str[1]);
	all->alloc[0] = 1;
	all->cmd1 = ft_split(str[2], ' ');
	if (!all->cmd1)
		ft_error(all, strerror(errno));
	all->alloc[1] = 1;
	all->cmd2 = ft_split(str[3], ' ');
	if (!all->cmd2)
		ft_error(all, strerror(errno));
	all->alloc[2] = 1;
	all->outfile = ft_copy(all, str[4]);
	all->alloc[3] = 1;
	return (all);
}
