/*
** delete_player_from_map.c for map in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Mon May 16 01:05:46 2011 axel catusse
** Last update Mon May 16 01:06:05 2011 axel catusse
*/

#include <sys/types.h>
#include "lemipc.h"

int			delete_player_from_map(t_lemipc *lemipc)
{
  if (lock_sem_id(lemipc->game->sem_id) == ERROR_VALUE)
    return (ERROR_VALUE);
  lemipc->game->map[lemipc->player.pos.y][lemipc->player.pos.x] = EMPTY_CASE;
  if (unlock_sem_id(lemipc->game->sem_id) == ERROR_VALUE)
    return (ERROR_VALUE);
  return (SUCCESS_VALUE);
}
