/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 06:14:59 by kdustin           #+#    #+#             */
/*   Updated: 2020/12/27 23:53:01 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_sim_commands(t_list *sim_cmds)
{
	int			i;
	int			j;
	t_sim_cmd	*sc;

	j = 0;
	while (sim_cmds != NULL)
	{
		sc = (t_sim_cmd*)(sim_cmds->content);
		ft_putstr_fd("\tPrint simple command number: ", 1);
		ft_putnbr_fd(j, 1);
		ft_putstr_fd("\n", 1);
		i = 0;
		ft_putstr_fd("\tArgs: ", 1);
		while (i < sc->argc)
		{
			ft_putstr_fd("\"", 1);
			ft_putstr_fd(sc->args[i], 1);
			ft_putstr_fd("\"", 1);
			ft_putstr_fd(" ", 1);
			i++;
		}
		ft_putstr_fd("\n\tIn file: ", 1);
		ft_putstr_fd(sc->in_file, 1);
		ft_putstr_fd(" Out file: ", 1);
		ft_putstr_fd(sc->out_file, 1);
		ft_putstr_fd(" Append: ", 1);
		ft_putunbr_fd(sc->is_append, 1);
		ft_putstr_fd("\n\n", 1);
		j++;
		sim_cmds = sim_cmds->next;
	}
}

void print_commands(t_list *cmds)
{
	int		i;
	t_cmd	*c;

	i = 0;
	while (cmds != NULL)
	{
		ft_putstr_fd("Print command number: ", 1);
		ft_putnbr_fd(i, 1);
		ft_putstr_fd("\n", 1);
		c = ((t_cmd*)(cmds->content));
		print_sim_commands(c->sim_cmds);
		ft_putstr_fd("\n", 1);
		i++;
		cmds = cmds->next;
	}
}

int main(void)
{
	t_list	*result;
	t_list	*commands;

	add_env_var(&g_env_vars, ft_strdup("PWD"), ft_strdup("/Users/diordychukdmitry"));
	add_env_var(&g_env_vars, ft_strdup("321"), ft_strdup("three-two-one"));
	add_env_var(&g_env_vars, ft_strdup("fdsgbkldmbklfdsmklfmd"), ft_strdup("trash"));
	//result = run_lexer("User input");
	//result = run_lexer("ls ; ls");
	//result = run_lexer(";dasd");
	//result = run_lexer("wasd;");
	//result = run_lexer(";;;;");
	//result = run_lexer("sfas;df;asd;fas;df;");
	//result = run_lexer(";asdf;dfas;");
	//result = run_lexer(";sdfsa;fasd");
	//result = run_lexer("fasdfasdf");
	//result = run_lexer("'Hello, wolrd'");
	//result = run_lexer("'fasdf>sadf'");
	//result = run_lexer("'Strong\"Week\"'");
	//result = run_lexer("\"week'strong'\"");
	//result = run_lexer(">>");
	//result = run_lexer(">");
	//result = run_lexer("<");
	//result = run_lexer("<><><>>>");
	//result = run_lexer("$$?");
	//result = run_lexer("3iO;KXC34G8oBErk");
	//result = run_lexer("$fS|6k|kVoZRgy90");
	//result = run_lexer(";$?$4<d2d>b3|;5a");
	//result = run_lexer("bc7$d6>|cee<875?");
	//result = run_lexer("42'd72c52a|'|db3");
	//result = run_lexer("be'7|\"e9477\'da;;");
	//result = run_lexer("\"ab\"9\"ab\"4;");
	//result = run_lexer("\"ab\"9");
	//result = run_lexer("4?|<<64'5<;9>>9$?a9$'$");
	//result = run_lexer("dsa'das");
	//result = run_lexer("'\"");
	//result = run_lexer("'$'");
	//result = run_lexer("\"$?\"");
	//result = run_lexer("Hi ' 42 ' world");
	//result = run_lexer(";;");
	//result = run_lexer(";");
	//result = run_lexer("|");
	//result = run_lexer("||");
	//result = run_lexer(";@@;");
	//result = run_lexer("| |");
	//result = run_lexer("ls;;");
	//result = run_lexer("ls; ;");
	//result = run_lexer("ls||");
	//result = run_lexer("ls | |");
	//result = run_lexer("echo $321");
	//result = run_lexer("echo $fdsgbkldmbklfdsmklfmd");
	//result = run_lexer("echo str1\"'str2'\"");                              //27
	//result = run_lexer("echo str1'\"str2\"'");
	//result = run_lexer("echo str1\"'$str2'\"");
	//result = run_lexer("echo str1'\"$str2\"'");
	//result = run_lexer("echo 'str1'str2\"str3 $PWD str4\" \"str5\"'$PWD' $PWD \"$PWD\"");
	//result = run_lexer("echo \"hello><; word\"");
	//result = run_lexer("echo $hfkdghldf$PWD");
	//result = run_lexer("echo '\"\"\"\"'");
	//result = run_lexer("echo \"\"''\"\"");
	//result = run_lexer("echo \" '''''' \"");
	//result = run_lexer("echo \"\"\"\"\"\"\"\"");
	//result = run_lexer("echo ''''''''");
	result = run_lexer("echo \"\"\"\"\"\"\"\"\"\"              :\"\"");      //36
	//result = run_lexer("\\\"");
	//result = run_lexer("\\'\\'");
	//result = run_lexer("\"\\'\"");
	//result = run_lexer("'\\'");
	//result = run_lexer("a $PWD b");
	//result = run_lexer(" ");
	//result = run_lexer("' '");
	//result = run_lexer(" ' ' ");
	//result = run_lexer(" ' \" \" ' ");
	//result = run_lexer(" \" ' ' \" ");
	//result = run_lexer("te\\$ta");
	//result = run_lexer("$$$");
	//result = run_lexer("\\\"teta");
	//result = run_lexer("");
	//result = run_lexer("echo d$PWD");
	//result = run_lexer("a|b|>what cat | hm");
	//result = run_lexer("a;b;>what cat ; hm");
	commands = run_parser(result);
	ft_putstr_fd("\n", 1);
	print_commands(commands);
	return (0);
}
