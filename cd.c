/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 20:33:37 by algaboya          #+#    #+#             */
/*   Updated: 2025/01/31 18:30:35 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_builtin(t_shell *general)
{
	int		status;
	char	*cwd;
	char	*newCWD;

	cwd = getcwd(NULL, 0);
	status = SUCCESS_EXIT;
	if (!general->cmd_lst->args[1])
		status = change_home(general);
	else if (general->cmd_lst->args[1] \
		&& ft_strcmp(general->cmd_lst->args[1], "-") == 0)
		status = change_prev_dir(general);
	else if (general->cmd_lst->args[1])
		status = change_dir(general->cmd_lst->args[1]);
	newCWD = getcwd(NULL, 0);
	if (!newCWD)
	{
		free_set_null(cwd);
		return (perror("cd: "), FAILURE_EXIT);
	}
	change_env_value(general->env_lst, "PWD", newCWD);
	change_env_value(general->sorted_env_lst, "PWD", newCWD);
	change_env_value(general->env_lst, "OLDPWD", cwd);
	change_env_value(general->sorted_env_lst, "OLDPWD", cwd);
	free_set_null(cwd);
	return (status);
}

int	change_dir(char *dir)
{
	int		status;

	status = chdir(dir);
	if (status != 0)
	{
		printf(" cd: %s: No such file or directory\n", dir);
		return (FAILURE_EXIT);
	}
	return (EXIT_SUCCESS);
}

int	change_home(t_shell *general)
{
	char	*home;

	home = get_value(general, "HOME");
	if (!home)
		return (write(STDERR_FILENO, "HOME is not set", ft_strlen("HOME is not set")));
	else if (chdir(home) < 0)
	{
		perror("cd: ");
		return errno;
	}
	return (EXIT_SUCCESS);
}

int	change_prev_dir(t_shell *general)
{
	char	*prev;
	char	*msg;

	prev = get_value(general, "OLDPWD");
	if (!prev)
		return (perror("minisHell: cd: OLDPWD not set\n"), FAILURE_EXIT);
	else if (chdir(prev) < 0)
	{
		msg = strerror(errno);
		return write(STDERR_FILENO, msg, ft_strlen(msg));
	}
	return (EXIT_SUCCESS);
}

char	*get_value(t_shell *general, char *keyik)
{
	t_env	*tmp;

	tmp = general->env_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, keyik) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	change_env_value(t_env *lst, char *keyik, char *valik)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, keyik) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(valik);
			if (!tmp->value)
				return (FAILURE_EXIT);
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
