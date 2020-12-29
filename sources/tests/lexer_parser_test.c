/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 06:14:59 by kdustin           #+#    #+#             */
/*   Updated: 2020/12/29 11:22:31 by kdustin          ###   ########.fr       */
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
			//ft_putstr_fd("\"", 1);
			ft_putstr_fd(sc->args[i], 1);
			//ft_putstr_fd("\"", 1);
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
	//result = run_lexer("echo \"\"\"\"\"\"\"\"\"\"              :\"\"");      //36
	//result = run_lexer("echo \"\"  :\"\"");
	//result = run_lexer("echo \"\"\"\"\"\"\"\"\"\",         wtf     :\"\"");
	//result = run_lexer("echo \"\"\"\"\"\"\"\"\"\",         wtf     :\"\"");
	//result = run_lexer("echo '\"\"\"\"\"\"\"\"\"\",         wtf     :\"\"'");
	//result = run_lexer("echo hello                       happy                               man");
	//result = run_lexer("export = ; echo $?");
	//result = run_lexer("echo $?");
	//result = run_lexer("export str1 2str = _3str str4=str5 ");             ??????????
	//result = run_lexer(" 'e'\"x\"p'o'r't'");
	//result = run_lexer(" \"'e'\"x\"p'o'r't'\""); 						//error
	//result = run_lexer("ec\"ho\" $str1 $str4");
	//result = run_lexer(" 'export' 'q'=e \"w\"=c e=\"h\" r='o' 't'='x' \"y\"=\"p\" u=r i=t");
	//result = run_lexer("  'e'\"x\"p'o'r't' \"t\"$q's'$i='h'\"e\"'l'l$r");
	//result = run_lexer("echo \"hello;\"; $q'c'\"h\"o $test");
	//result = run_lexer("echo \"hello;\"; $q'c'\"h\"o $test");               //50
	//result = run_lexer("$q$w$e'o' $PWD;   cd .. ;    $q\"c\"$e'o' $PWD    ;");
	//result = run_lexer("$lkjlkjllkdfs$q$w$e$r \"$e\"$q\"l\"'l'$r;");
	//result = run_lexer(" echo         \\'\\\"\\\\");
	//result = run_lexer("echo ~");
	//result = run_lexer("echo hello sad man");
	//result = run_lexer("echo $?");
	//result = run_lexer(">fil$q'1' e$w\"ho\" s$i\"r\"ing f$r$u file1");
	//result = run_lexer("pwd ; cat file1");
	//result = run_lexer("ls lskdgjdhgisdoigjiredg");
	//result = run_lexer("unset PWD; echo $PWD");
	//result = run_lexer("ls; unset PATH; ls     ;");                         //64
	//result = run_lexer("export PATH=/  ; ls");
	//result = run_lexer("export PATH=/bin  ; ls");
	//result = run_lexer("exit 1234;ls");
	//result = run_lexer("echo $PWD; unset PWD");
	//result = run_lexer("echo $PWD; export PWD=/ ; echo $PWD;");
	//result = run_lexer("pwd; echo $PWD");
	//result = run_lexer("cd; echo $PWD; cd -");
	//result = run_lexer("echo $PWD; echo $OLDPWD");
	//result = run_lexer("unset OLDPWD; echo $OLDPWD");
	//result = run_lexer("cd; echo $OLDPWD");
	//result = run_lexer("cd ; echo $PWD; echo $OLDPWD");
	//result = run_lexer("cd -");
	//result = run_lexer("ls -la");
	//result = run_lexer("ls \"-la\" ; cd -");
	//result = run_lexer("echo '\'");
	//result = run_lexer("echo \\hello \\$PWD");                              //84
	//result = run_lexer("echo '\\hello  \\$PWD'");
	//result = run_lexer("echo \"\\hello  \\$PWD\"");
	//result = run_lexer("echo \\'\\\"\\\\ \"\\hello\\$PWD\"");
	//result = run_lexer("echo \"\\$PWD\" \"\\PWD\" ");
	//result = run_lexer("echo \"\\\"\"");
	//result = run_lexer("echo \"\\'\"");
	//result = run_lexer("\"echo f\" hello");
	//result = run_lexer(">\"helo l\" echo hell\\ f");
	//result = run_lexer(">>\"helo l\" echo hell\\ f ; echo hell\\ f");
	//result = run_lexer("export t=n; echo -$t -n \"-\"'n' hello");
	//result = run_lexer("echo -$t \"-n\" '-''n' '-n;'         -n hello");
	//result = run_lexer("export a=l d=s; $a$d");
	//result = run_lexer("echo $PWD > as ; cat as");
	//result = run_lexer("echo ''\\''\"a|\"\\'q'a'\\a'w'");
	//result = run_lexer("echo \\\"\\|\\;\\\"\\| cat -e > \\q\\w\\e\\r\\t\\y ; cat qwerty");
	//result = run_lexer("pwd >a1>a2>a3; echo s1 >q1 s2>q2 s3; cat a2; cat a3; cat q1; cat q2; ");  //100
	//result = run_lexer("echo");
	//result = run_lexer("echo \\ \\\\");
	//result = run_lexer("echo hello '\\' ';' \"   '\\' \\\" \" \\\" \"$PWD\\\\\\\"\\~\\;\"\\; >> t1 \\' \\ \\ \\\\");
	//result = run_lexer("echo hello '\\' ';' \"   '\\' \\\" \" \\\" \"$PWD\\\\\\\"\\~\\;\"\\; >> t1 \\' \\ \\ \\\\; cat t1");
	//result = run_lexer("\\ls\\ ;");
	//result = run_lexer("export echo=\"echo hello\";$echo");
	//result = run_lexer("export echo=\"echo hello $echo\"; $echo");
	//result = run_lexer("exit 9854679547698675497885947");
	//result = run_lexer("exit -9854679547698675497885948");
	//result = run_lexer("export a1=a2 ; export a2=' a3' ; export a1=hello$a2=poka");

	//result = run_lexer("export baba=lol | echo $baba >> out| export baba=kek | echo $baba >> out");
	//result = run_lexer("cat /dev/random | head -c 100 | wc -c");
	//result = run_lexer("ls > 2 | ls > 3");
	//result = run_lexer("$?|$?");
	//result = run_lexer("echo \\\\");
	//result = run_lexer("echo '-n;' hello");
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
	//result = run_lexer("$");
	//result = run_lexer("$$");
	//result = run_lexer("$$$");
	//result = run_lexer("\\\"teta");
	//result = run_lexer("");
	//result = run_lexer("echo d$PWD");
	//result = run_lexer("a|b|>what cat | hm");
	result = run_lexer("a;b;>what cat ; hm");
	commands = run_parser(result);
	ft_putstr_fd("\n", 1);
	print_commands(commands);
	return (0);
}
