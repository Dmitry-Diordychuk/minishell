/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:02:02 by kdustin           #+#    #+#             */
/*   Updated: 2020/12/17 16:15:13 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>

/*
**	Error handling.
*/

void error(char *message);

/*
**	Command table structures.
*/

typedef struct			s_sim_cmd
{
	int					n_avble_args;
	int					n_args;
	char				**args;
}						t_sim_cmd;
t_sim_cmd				*create_sim_cmd();
int						insert_arg(t_sim_cmd *sim_cmd, char *arg);

typedef struct			s_cmd
{
	int					n_avble_sim_cmds;
	int					n_sim_cmds;
	t_sim_cmd			*sim_cmds;
	char				*out_file;
	char				*in_file;
	char				*err_file;
	int					background;
}						t_cmd;

t_cmd					g_cur_cmd;
t_sim_cmd				*g_cur_sim_cmd;

void					free_args(char **args);
int						enlarge_args(t_sim_cmd *sim_cmd, char *new_arg);

#endif
