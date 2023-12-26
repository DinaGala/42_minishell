/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:52:26 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/26 18:40:08 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export_plus_equal(t_mini *sh, char *key, char *value)
{
	t_env	*env;
	char	*old_value;
	char	*env_value;

	
	env_value = find_in_env_variables(sh, key);
	if (!env_value)
		return ((void)add_or_update_env(sh, key, value));
	else
	{
		env = sh->env_lst;
		if (!value)
			value = ft_strdup("");
		while (env != NULL)
		{
			if (ft_strncmp(env->env_key, key, ft_strlen(key)) == 0 \
				&& ft_strlen(env->env_key) == ft_strlen(key))
			{
				old_value = env->env_val;
				env->env_val = ft_strjoin(old_value, value);
				free(old_value);
				return ;
			}
			env = env->next;
		}
	}
}

int	error_option(char *str1, char *str2, char **vc)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd("=", 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	vc = arr_clean(vc, 0);
	return (1);
}

int	handle_args(t_mini *sh, char *arg)
{
	char	**vc;
	char	*key;

	vc = ft_split(arg, '=');
//	printf("[EXPORT Handle Args] Entered handle args, vc: %s\n", *vc); //erase
//	print_arr(vc);	
	if (!export_option(vc[0]))
		return (error_option(vc[0], vc[1], vc));
	else
	{
//		printf("[EXPORT Handle Args] Entered else, vc: %s\n", *vc); //erase
		if (ft_strchr(vc[0], '+'))
		{
			key = ft_substr(vc[0], 0, ft_strchr(vc[0], '+') - vc[0]);
			if (!key)
				return (1);
			export_plus_equal(sh, key, vc[1]);
			free(key);
		}
		else
			add_or_update_env(sh, vc[0], vc[1]);
	}
//	printf("[EXPORT] before arr clean: %i\n", 2); //erase
	vc = arr_clean(vc, 0);
	return (0);
}

int	ft_export(t_mini *sh, t_pipe *p)
{
	t_env	*tmp_env;
	char	**t_cmd;
	int		err;
	int		i;

	err = 0;
//	printf("[EXPORT] Entered EXPORT: %i\n", err); //erase
	tmp_env = sh->env_lst;
	t_cmd = p->cmd;
	i = 1;
	if (!t_cmd[1])
		return (print_export(tmp_env, p));
//	printf("[EXPORT] After pri nt EXPORT: %i\n", err); //erase
	while (t_cmd[i])
	{
		if (!err)
			err = handle_args(sh, t_cmd[i]);
		else
			handle_args(sh, t_cmd[i]);
		i++;
	}
//	printf("[EXPORT] Before env conv: %i\n", err); //erase
	if (sh->env)
		sh->env = arr_clean(sh->env, 0);
	sh->env = env_converter(sh->env_lst);
	return (err);
}
