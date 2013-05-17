/*
** free_ipc.c for free_ipc in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Sun May 15 04:23:54 2011 axel catusse
** Last update Sun May 15 04:27:58 2011 axel catusse
*/

#include <stdlib.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "lemipc.h"

int			free_ipcs(t_lemipc *lemipc)
{
  if (msgctl(lemipc->game->msg_id, IPC_RMID, NULL) < 0)
    return (raise_error("msgclt", ERROR_VALUE));
  if (semctl(lemipc->game->sem_id, 0, IPC_RMID) < 0)
    return (raise_error("semclt", ERROR_VALUE));
  if (shmctl(lemipc->shm_id, IPC_RMID, NULL) < 0)
    return (raise_error("shmclt", ERROR_VALUE));
  if (shmdt(lemipc->game) == ERROR_VALUE)
    return (raise_error("shmdt", ERROR_VALUE));
  return (SUCCESS_VALUE);
}
