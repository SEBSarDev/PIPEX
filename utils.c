/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 20:16:39 by ssar              #+#    #+#             */
/*   Updated: 2021/06/13 21:05:50 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_free_tab(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != 0)
	{
		free((void *)ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

void	my_exit(t_pipex *all, int sortie)
{
	if (all->alloc[0] == 1)
		free(all->infile);
	if (all->alloc[1] == 1)
		ft_free_tab(all->cmd1);
	if (all->alloc[2] == 1)
		ft_free_tab(all->cmd2);
	if (all->alloc[3] == 1)
		free(all->outfile);
	free((void *)all);
	exit(sortie);
}

int	ft_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_error(t_pipex *all, char *str)
{
	write(2, str, ft_len(str));
	my_exit(all, 1);
}

char	*ft_copy(t_pipex *all, char *str)
{
	char	*new;
	int		len;
	int		i;

	i = 0;
	len = ft_len(str);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		ft_error(all, strerror(errno));
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[len] = '\0';
	return (new);
}
