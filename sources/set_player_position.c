/*
** set_position_of_player.c for set in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Sun May 15 04:37:05 2011 axel catusse
** Last update Mon May 16 01:31:32 2011 axel catusse
*/

#include <sys/param.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "lemipc.h"

static int		_is_empty_case(t_lemipc *lemipc)
{
  int			x;
  int			y;

  x = rand() % MAP_SIZE_SIDE;
  y = rand() % MAP_SIZE_SIDE;
  if (lemipc->game->map[y][x] == EMPTY_CASE)
    {
      lemipc->player.pos.x = x;
      lemipc->player.pos.y = y;
      lemipc->game->map[y][x] = lemipc->player.team;
      return (SUCCESS_VALUE);
    }
  return (ERROR_VALUE);
}

int			set_player_position(t_lemipc *lemipc)
{
  int			nb_place;
  char			found;

  if ((nb_place = count_id_map(lemipc, EMPTY_CASE)) == ERROR_VALUE)
    return (ERROR_VALUE);
  else if (nb_place <= MAP_SIZE_SIDE)
    {
      fprintf(stderr, "error: map is (almost ~10%%) full\n");
      return (ERROR_VALUE);
    }
  if (lock_sem_id(lemipc->game->sem_id) == ERROR_VALUE)
    return (ERROR_VALUE);
  found = 0;
  while (!found)
    {
      if (_is_empty_case(lemipc) == SUCCESS_VALUE)
	found = 1;
    }
  if (unlock_sem_id(lemipc->game->sem_id) == ERROR_VALUE)
    return (ERROR_VALUE);
  return (SUCCESS_VALUE);
}
