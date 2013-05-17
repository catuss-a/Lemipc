/*
** player_random_move.c for le in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Mon May 16 01:07:56 2011 axel catusse
** Last update Sun May 22 19:45:12 2011 axel catusse
*/

#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include "lemipc.h"

static void		fill_futur_pos(t_lemipc *lemipc,
				       t_coord2d *futur_pos)
{
  futur_pos->x = lemipc->player.pos.x + (rand() % 3 - 1);
  futur_pos->y = lemipc->player.pos.y
    + (futur_pos->x == lemipc->player.pos.x ?
       rand() % 2 ? -1 : 1 : 0);
}

int			player_random_move(t_lemipc *lemipc)
{
  char			moved;
  t_coord2d		futur_pos;

  moved = KO;
  while (!moved)
    {
      fill_futur_pos(lemipc, &futur_pos);
      if (lock_sem_id(lemipc->game->sem_id) == ERROR_VALUE)
	return (ERROR_VALUE);
      if (futur_pos.x >= 0 && futur_pos.x < MAP_SIZE_SIDE
	  && futur_pos.y >= 0 && futur_pos.y < MAP_SIZE_SIDE
	  && lemipc->game->map[futur_pos.y][futur_pos.x] == EMPTY_CASE)
	{
	  lemipc->game->map[lemipc->player.pos.y][lemipc->player.pos.x]
	    = EMPTY_CASE;
	  lemipc->player.pos.x = futur_pos.x;
	  lemipc->player.pos.y = futur_pos.y;
	  lemipc->game->map[futur_pos.y][futur_pos.x] = lemipc->player.team;
	  moved = OK;
	}
      if (unlock_sem_id(lemipc->game->sem_id) == ERROR_VALUE)
	return (ERROR_VALUE);
    }
  return (SUCCESS_VALUE);
}
