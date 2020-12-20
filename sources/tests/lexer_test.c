/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 06:14:59 by kdustin           #+#    #+#             */
/*   Updated: 2020/12/20 14:36:12 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_token(void* container)
{
	t_token	*token;

	token = (t_token*)container;
	ft_putstr_fd("{", 1);
	if (token->name == SEPARATOR)
		ft_putstr_fd("Separator", 1);
	else if (token->name == STRONG_QUOTE)
		ft_putstr_fd("Strong quote", 1);
	else if (token->name == WEAK_QUOTE)
		ft_putstr_fd("Weak quote", 1);
	else if (token->name == LESS)
		ft_putstr_fd("Less", 1);
	else if (token->name == GREAT)
		ft_putstr_fd("Greate", 1);
	else if (token->name == GREATGREAT)
		ft_putstr_fd("Greate greate", 1);
	else if (token->name == PIPE)
		ft_putstr_fd("Pipe", 1);
	else if (token->name == LAST_RESULT)
		ft_putstr_fd("Last result", 1);
	else if (token->name == ENV)
		ft_putstr_fd("Enviroment value", 1);
	if (token->name == WORD)
	{
		ft_putstr_fd("Word", 1);
		ft_putstr_fd(", \"", 1);
		ft_putstr_fd(token->value, 1);
		ft_putstr_fd("\"} ", 1);
	}
	else
		ft_putstr_fd(", \"\"} ", 1);
}

void print_tokens(t_list *tokens)
{
	ft_lstiter(tokens, print_token);
}

int main(void)
{
	t_list	*result;

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
	print_tokens(result);
	return (0);
}
