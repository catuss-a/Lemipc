/*
** x_IMG_Load.c for load in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Sun May 22 19:49:07 2011 axel catusse
** Last update Sun May 22 19:50:18 2011 axel catusse
*/

#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL_rotozoom.h>
#include <sys/types.h>
#include "lemipc.h"

SDL_Surface             *x_IMG_Load(char *path)
{
  SDL_Surface           *ptr;

  if ((ptr = IMG_Load(path)) == NULL)
    return ((SDL_Surface*)raise_error("IMG_Load\n", ERROR_VALUE));
  return (ptr);
}
