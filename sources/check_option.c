/*
** check_option.c for lemipc in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Sun May 15 03:41:10 2011 axel catusse
** Last update Sun May 22 18:47:37 2011 axel catusse
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "lemipc.h"

int			check_option(t_lemipc *lemipc, int argc, char **argv)
{
  int			c;

  while ((c = getopt(argc, argv, "t:vsqr")) != -1)
    {
      if (c == 't')
	{
	  lemipc->opt |= FLAG_TEAM;
	  lemipc->player.team = atoi(optarg);
	}
      else if (c == 'v')
	lemipc->opt |= FLAG_VERBOSE;
      else if (c == 'q')
	lemipc->opt |= FLAG_QUIT;
      else if (c == 's')
	lemipc->opt |= FLAG_START;
      else if (c == 'r')
	lemipc->opt |= FLAG_FREE;
      else if (c == '?')
	return (ERROR_VALUE);
    }
  if ((lemipc->opt & FLAG_TEAM) != FLAG_TEAM)
    return (ERROR_VALUE);
  return (SUCCESS_VALUE);
}
