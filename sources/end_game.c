/*
** end_game.c for lol in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Sun May 22 19:18:00 2011 axel catusse
** Last update Sun May 22 19:22:02 2011 axel catusse
*/

#include <sys/types.h>
#include "lemipc.h"

int			end_game(t_lemipc *lemipc)
{
  int			id;
  int			x;
  int			y;

  if (lock_sem_id(lemipc->game->sem_id) == ERROR_VALUE)
    return (ERROR_VALUE);
  id = 0;
  y = -1;
  while (++y < MAP_SIZE_SIDE)
    {
      x = -1;
      while (++x < MAP_SIZE_SIDE)
	{
	  if (lemipc->game->map[y][x] != EMPTY_CASE)
	    {
	      if (id == 0)
		id = lemipc->game->map[y][x];
	      else if (id != lemipc->game->map[y][x])
		return (unlock_sem_id(lemipc->game->sem_id));
	    }
	}
    }
  if (unlock_sem_id(lemipc->game->sem_id) == ERROR_VALUE)
    return (ERROR_VALUE);
  return (QUIT);
}
