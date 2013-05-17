/*
** player_move.c for player move in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Sun May 22 19:16:57 2011 axel catusse
** Last update Sun May 22 19:39:31 2011 axel catusse
*/

#include <sys/types.h>
#include "lemipc.h"

int			player_move(t_lemipc *lemipc)
{
  int			ret;
  t_coord2d		enemy;

  if ((ret = message_from_ally(lemipc, &enemy)) == ERROR_VALUE)
    return (ERROR_VALUE);
  if (ret == MESSAGE_RECV)
    {
      if ((ret = GET_ID_FROM_MAP(lemipc, enemy.x, enemy.y))
	  != lemipc->player.team && ret != EMPTY_CASE)
	if (message_to_send(lemipc, &enemy) == ERROR_VALUE)
	  return (ERROR_VALUE);
      move_player_to_enemy(lemipc, &enemy);
    }
  else
    {
      if ((ret = enemy_in_player_range(lemipc, &enemy)) == ERROR_VALUE)
	return (ERROR_VALUE);
      if (ret == MESSAGE_TO_SEND)
	return (message_to_send(lemipc, &enemy) == ERROR_VALUE ? ERROR_VALUE :
		move_player_to_enemy(lemipc, &enemy));
      else return (player_random_move(lemipc));
    }
  return (SUCCESS_VALUE);
}
