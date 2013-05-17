/*
** raise_error.c for raise_error in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Sat May 14 20:03:34 2011 axel catusse
** Last update Sat May 14 20:05:21 2011 axel catusse
*/

#include <stdio.h>
#include <stdlib.h>

int			raise_error(char *binary, int return_value)
{
  perror(binary);
  return (return_value);
}
