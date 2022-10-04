/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 20:26:11 by ssar              #+#    #+#             */
/*   Updated: 2021/06/14 10:38:25 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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
		ft_error(all, strerror(errno), NULL);
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

void	free_path(t_pipex *all, char *val, char **path, char *word)
{
	if (val != NULL)
		free(val);
	if (path != NULL)
		ft_free_tab(path);
	if (word != NULL)
		ft_error(all, "Command not found", word);
	ft_error(all, strerror(errno), NULL);
}

void	free_all_path(char **path, char **path_complete, char *value)
{
	ft_free_tab(path);
	ft_free_tab(path_complete);
	free(value);
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
		{
			ft_free_tab(path_complete);
			free_path(all, value, path, word);
		}
		i++;
	}
	free_all_path(path, path_complete, value);
}
