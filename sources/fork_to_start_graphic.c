/*
** fork_to_start_graphic.c for grphic in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Mon May 16 00:57:25 2011 axel catusse
** Last update Mon May 16 01:01:59 2011 axel catusse
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include "lemipc.h"

int			fork_to_start_graphic(t_lemipc *lemipc)
{
  int			pid;

  printf("launch graphic process.\n");
  if ((pid = fork()) == ERROR_VALUE)
    return (raise_error("fork", ERROR_VALUE));
  if (!pid)
    {
      (void)start_graphic(lemipc);
      exit(EXIT_SUCCESS);
    }
  return (SUCCESS_VALUE);
}
