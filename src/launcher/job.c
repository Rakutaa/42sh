/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:22:21 by vkuokka           #+#    #+#             */
/*   Updated: 2021/03/04 21:41:54 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			launch_job(t_job *job, int foreground)
{
	t_process	*process;
	pid_t		pid;
	int			mypipe[2];
	int			infile;
	int			outfile;

	infile = job->stdin;
	process = job->first_process;
	while (process)
	{
		if (process->next)
		{
			if (pipe(mypipe) < 0)
			{
				exit(1);
			}
			outfile = mypipe[1];
		}
		else
			outfile = job->stdout;
		pid = fork();
		if (pid == 0)
			launch_process(process, job->pgid, infile, outfile, job->stderr, foreground);
		else if (pid < 0)
			exit(1);
		else
		{
			process->pid = pid;
			if (g_shell->mode & INTERACTIVE)
			{
				if (!job->pgid)
					job->pgid = pid;
				setpgid(pid, job->pgid);
			}
		}
		if (infile != job->stdin)
			close(infile);
		if (outfile != job->stdout)
			close(outfile);
		infile = mypipe[0];
		process = process->next;
	}
	format_job_info(job, "launched");
	if (!g_shell->mode & INTERACTIVE)
		wait_for_job(job);
	else if (foreground)
		put_job_in_foreground(job, 0);
	else
		put_job_in_background(job, 0);
}