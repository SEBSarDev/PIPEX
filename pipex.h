/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 15:04:26 by ssar              #+#    #+#             */
/*   Updated: 2021/06/14 09:52:46 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/types.h>

typedef struct s_pipex
{
	char	*infile;
	char	**cmd1;
	char	**cmd2;
	char	*outfile;
	int		save_stdout;
	int		alloc[4];
}		t_pipex;

char	**ft_split(const char *str, char c);
void	redir_out(t_pipex *all);
void	redir_in(t_pipex *all);
void	launch_exec_cmd_path(t_pipex *all, char *w, char **lst, char **envp);
char	**join_word(char **path, char *word);
t_pipex	*get_arguments(t_pipex *all, char **str);
char	*ft_copy(t_pipex *all, char *str);
void	ft_error(t_pipex *all, char *str, char *w);
int		ft_len(char *str);
void	my_exit(t_pipex *all, int sortie);
char	*ft_free_tab(char **ptr);

#endif
