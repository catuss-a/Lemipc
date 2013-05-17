/*
** message_from_ally.c for mess recu in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Wed May 18 01:17:51 2011 axel catusse
** Last update Wed May 18 04:55:14 2011 axel catusse
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "lemipc.h"

int			message_from_ally(t_lemipc *lemipc, t_coord2d *enemy)
{
  int			ret;
  t_msgbuf		msg_rcv;

  if ((ret = msgrcv(lemipc->game->msg_id, &msg_rcv, sizeof(msg_rcv),
		    lemipc->player.team, IPC_NOWAIT)) == ERROR_VALUE)
    return (SUCCESS_VALUE);
  if (ret > 0)
    {
      enemy->x = mystring_to_int(msg_rcv.mtext, 0);
      enemy->y = mystring_to_int(msg_rcv.mtext, 8);
      return (MESSAGE_RECV);
    }
  return (SUCCESS_VALUE);
}
