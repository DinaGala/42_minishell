#include "../../include/minishell.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>

#define ERR_MLC	-2
#define ERR_KEY	-1
#define	NOTHING	0
#define UPDATE	1
#define ADD		2

int		print_export(t_env *eprint, t_pipe *p)
{
	t_env	*tmp;
	int		output;

	output = p->out_fd;
	if (output < 1)
		output = 1;
	if (!eprint)
		return (1);
	print_sort_print(eprint);
	tmp = eprint;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", output);
		ft_putstr_fd(tmp->env_key, output);
		if (tmp->env_val)
		{
			ft_putstr_fd("=", output);
			ft_putstr_fd("\"", output);
			ft_putstr_fd(tmp->env_val, output);
			ft_putstr_fd("\"", output);
			write(1, "\n", output);
		}
		else
			ft_putstr_fd("\n", output);
		tmp = tmp->next;
	}
	tmp = eprint;
	return (0);
}

char	*find_in_env_variables(t_mini *sh, char *variable_name)
{
	t_env	*env;
	int		env_name_len;
	int		var_name_len;

	if (variable_name == NULL)
		return (NULL);
	env = sh->env_lst;
	var_name_len = ft_strlen(variable_name);
	while (env != NULL)
	{
		env_name_len = ft_strlen(env->env_key);
		if (ft_strncmp(env->env_key, variable_name, env_name_len) == 0
			&& (env_name_len == var_name_len))
			return (env->env_val);
		env = env->next;
	}
	return (NULL);
}

t_env	*ft_getkey_node(char *new_key, t_env *list)
{
	t_env	*head;
	
	head = list;
	while (list->next)
	{
		if (ft_strcmp(new_key, list->env_key) == 0)
			return (list);
		list = list->next;
	}
	list = head;
	return (NULL);

}

int		export_option(const char *name)
{
	int	i;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i] != '\0')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			if ((name[i] == '+' || name[i] == '=') && name[i + 1] != '\0')
				return (0);
		}
		i++;
	}
	return (1);
}
