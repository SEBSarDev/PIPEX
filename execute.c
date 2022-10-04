/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 20:26:11 by ssar              #+#    #+#             */
/*   Updated: 2021/06/13 20:55:05 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_val_path(t_pipex *all, char *str)
{
	int		i;
	int		count;
	char	*path;
	int		j;

	i = 0;
	count = 0;
	while (str[i] != '=')
		i++;
	while (str[++i])
		count++;
	path = (char *)malloc(sizeof(char) * (count + 1));
	if (!path)
		ft_error(all, strerror(errno));
	i = 0;
	while (str[i] != '=')
		i++;
	j = -1;
	while (str[++i])
		path[++j] = str[i];
	path[count] = '\0';
	return (path);
}

char	*get_env_path(t_pipex *all, char **envp)
{
	char	*path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
		&& envp[i][2] == 'T' && envp[i][3] == 'H' && envp[i][4] == '=')
			path = get_val_path(all, envp[i]);
		i++;
	}
	return (path);
}

void	free_path(t_pipex *all, char *val, char **path, char **path_c)
{
	if (val != NULL)
		free(val);
	if (path != NULL)
		ft_free_tab(path);
	if (path_c != NULL)
		ft_free_tab(path_c);
	ft_error(all, strerror(errno));
}

void	launch_exec_cmd_path(t_pipex *all, char *word, char **lst, char **envp)
{
	char	*value;
	char	**path;
	int		i;
	char	**path_complete;

	i = 0;
	value = get_env_path(all, envp);
	path = ft_split(value, ':');
	if (path == NULL)
		free_path(all, value, NULL, NULL);
	path_complete = join_word(path, word);
	if (path_complete == NULL)
		free_path(all, value, path, NULL);
	while (path_complete[i]
		&& execve(path_complete[i], lst, envp) == -1)
	{
		if (!path_complete[i + 1]
			&& execve(path_complete[i], lst, envp) == -1)
			free_path(all, value, path, path_complete);
		i++;
	}
	ft_free_tab(path);
	ft_free_tab(path_complete);
	free(value);
}
