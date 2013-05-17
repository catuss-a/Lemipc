/*
** message_to_send.c for  in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Wed May 18 03:37:06 2011 axel catusse
** Last update Sun May 22 19:22:25 2011 axel catusse
*/

#include <strings.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "lemipc.h"

void			int_to_mystring(char *buf, int nb, int begin)
{
  union u_itoa		ito;
  int			idx;

  bzero(&ito, sizeof(ito));
  ito.nb = nb;
  idx = -1;
  while (++idx < 8)
    buf[begin + idx] = ito.buf[idx];
}

int			mystring_to_int(char *src, int begin)
{
  union u_itoa		ito;
  int			idx;

  bzero(&ito, sizeof(ito));
  idx = -1;
  while (++idx < 8)
    ito.buf[idx] = src[begin + idx];
  return (ito.nb);
}

int			message_to_send(t_lemipc *lemipc, t_coord2d *enemy)
{
  t_msgbuf		msg_send;

  msg_send.mtype = lemipc->player.team;
  int_to_mystring(msg_send.mtext, enemy->x, 0);
  int_to_mystring(msg_send.mtext, enemy->y, 8);
  if (msgsnd(lemipc->game->msg_id, &msg_send, sizeof(msg_send), IPC_NOWAIT)
      == ERROR_VALUE)
    return (raise_error("msgsnd", ERROR_VALUE));
  return (SUCCESS_VALUE);
}
