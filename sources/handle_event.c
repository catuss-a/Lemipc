/*
** handle_event.c for handle event in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Sun May 22 19:47:59 2011 axel catusse
** Last update Sun May 22 19:52:01 2011 axel catusse
*/

#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL_rotozoom.h>
#include <sys/types.h>
#include "lemipc.h"

void			handle_event(void)
{
  SDL_Event		evt;

  if (SDL_PollEvent(&evt))
    if (evt.type == SDL_QUIT)
      live = 0;
}
