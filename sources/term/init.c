/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 17:47:11 by kdustin           #+#    #+#             */
/*   Updated: 2021/03/26 14:56:02 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_terminal_data(void)
{
	char	*termtype;
	int		success;

	termtype = getenv("TERM");
	if (termtype == 0)
	{
		printf("Specify a terminal type with `setenv TERM <yourtype>'.\n");
		return (ERROR);
	}
	success = tgetent(g_term_buffer, termtype);
	if (success < 0)
	{
		printf("Could not access the termcap data base.\n");
		return (ERROR);
	}
	if (success == 0)
	{
		printf("Terminal type `%s' is not defined.\n", termtype);
		return (ERROR);
	}
	return (SUCCESSED);
}

int	set_terminal_options(int on_off_define)
{
	static struct termios	savetty;
	struct termios			tty;

	if (on_off_define == ON)
	{
		if (!isatty(0))
			errno = ENXIO;
		if (!errno && tcgetattr(0, &tty) < 0)
			errno = ENXIO;
		if (errno)
			return (ERROR);
		savetty = tty;
		tty.c_lflag &= ~(ECHO | ICANON | ISIG);
		tty.c_cc[VMIN] = 1;
		tty.c_cc[VTIME] = 0;
		if (!errno && tcsetattr(0, TCSANOW, &tty) < 0)
			errno = ENXIO;
	}
	else if (on_off_define == OFF)
	{
		if (tcsetattr(0, TCSANOW, &savetty) < 0)
			errno = ENXIO;
	}
	return (errno ? ERROR : SUCCESSED);
}
