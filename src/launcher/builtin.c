/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:43:11 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/05 14:20:34 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int run_builtin(char **argv)
{
	if (ft_strequ(argv[0], "fc"))
		return (fc(argv));
	else if (ft_strequ(argv[0], "echo"))
		return (echo(argv));
	else if (ft_strequ(argv[0], "jobs"))
		return (jobs(argv));
	else if (ft_strequ(argv[0], "exit"))
		shell_exit();
	return (1);
}