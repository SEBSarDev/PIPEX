/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 20:40:22 by ssar              #+#    #+#             */
/*   Updated: 2021/06/13 21:12:55 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*fill_join_word(char **path, int i, char *word)
{
	int		j;
	int		k;
	int		count;
	char	*new;

	j = -1;
	k = -1;
	count = ft_len(path[i]) + ft_len(word);
	new = (char *)malloc(sizeof(char) * (count + 2));
	if (!new)
		return (NULL);
	while (path[i][++k])
		new[++j] = path[i][k];
	new[++j] = '/';
	k = -1;
	while (word[++k])
		new[++j] = word[k];
	new[++j] = '\0';
	return (new);
}

char	**join_word(char **path, char *word)
{
	char	**new_path;
	int		i;

	i = 0;
	while (path[i])
		i++;
	new_path = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_path)
		return (NULL);
	new_path[i] = 0;
	i = -1;
	while (path[++i])
	{
		new_path[i] = fill_join_word(path, i, word);
		if (new_path[i] == NULL)
		{
			ft_free_tab(new_path);
			return (NULL);
		}
	}
	return (new_path);
}
