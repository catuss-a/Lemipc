/*
** lemipc.h for lemipc in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Sat May 14 19:55:57 2011 axel catusse
** Last update Sun May 22 19:52:25 2011 axel catusse
*/

#ifndef LEMIPC_H_
# define LEMIPC_H_

/*
** INCLUDES
*/
# include <SDL/SDL.h>
# include <SDL_image.h>
# include <SDL_rotozoom.h>

/*
** ENUMERATIONS
*/

enum
  {
    EMPTY_CASE = 0,
    FULL_CASE
  };

enum player_type
  {
    ALL_PLAYER,
    MATE_PLAYER,
    ENEMY_PLAYER
  };

enum
  {
    KO = 0,
    OK,
    QUIT
  };

enum
  {
    ERROR_VALUE = -1,
    SUCCESS_VALUE,
    MESSAGE_RECV,
    MESSAGE_TO_SEND,
    MOVED,
    END_GAME
  };

/*
** -- DEFINES --
*/

# define PROJ_ID 11

# define MAP_SIZE_SIDE 30

# define FLAG_TEAM	(1 << 0)
# define FLAG_VERBOSE	(1 << 1)
# define FLAG_START	(1 << 2)
# define FLAG_QUIT	(1 << 3)
# define FLAG_FREE	(1 << 4)

/*
** Graphics
*/
# define SIZE_H_CASE 25
# define SIZE_W_CASE 34

/*
** Game
*/
# define PLAYER_RANGE 4

/*
** macros
*/
# define GET_ID_FROM_MAP(lemipc, x, y) (lemipc->game->map[y][x])

/*
** TYPEDEFS
*/

typedef int			id;
typedef enum player_type	player_type;

/*
** UNIONS
*/

union			semun
{
  int			val;
  struct semid_ds	*buf;
  unsigned short	*array;
  struct seminfo	*__buf;
};

union			u_itoa
{
  int			nb;
  char			buf[8];
};

/*
** STRUCTURES
*/

typedef struct		s_msgbuf
{
  long			mtype;
  char			mtext[16];
}			t_msgbuf;

typedef struct		s_coord2d
{
  int			x;
  int			y;
}			t_coord2d;

typedef struct		s_shared_mem
{
  int			map[MAP_SIZE_SIDE][MAP_SIZE_SIDE];
  char			start_game;
  int			sem_id;
  int			msg_id;
}			t_shared_mem;

typedef struct		s_player
{
  t_coord2d		pos;
  id			team;
}			t_player;

typedef struct		s_lemipc
{
  t_player		player;
  char			opt;
  key_t			key;
  int			shm_id;
  t_shared_mem		*game;
}			t_lemipc;

/*
** lemipc_loop's variables
*/
extern char		run;
extern char		live;

/*
** -- PROTOTYPES --
*/
int			raise_error(char *binary, int return_value);
int			init_shared_mem(t_lemipc *lemipc);
void			dump_memory(char **map);
int			check_option(t_lemipc *lemipc, int argc, char **argv);
int			launch_lemipc(t_lemipc *lemipc);
int			message_from_ally(t_lemipc *lemipc, t_coord2d *enemy);
int			init_game(t_lemipc *lemipc);
int			end_game(t_lemipc *lemipc);

/*
** graphic functions
*/
int			fork_to_start_graphic(t_lemipc *lemipc);
int			start_graphic(t_lemipc *lemipc);
int			display_map(t_lemipc *lemipc,
				    SDL_Surface *sprite_letters,
				    SDL_Surface *screen);
void			handle_event(void);
SDL_Surface             *x_IMG_Load(char *path);

/*
** player functions
*/
int			set_player_position(t_lemipc *lemipc);
int			player_random_move(t_lemipc *lemipc);
int			enemy_in_player_range(t_lemipc *lemipc, t_coord2d *enemy);
int			player_is_dead(t_lemipc *lemipc);
int			move_player_to_enemy(t_lemipc *lemipc, t_coord2d *enemy);
int			player_move(t_lemipc *lemipc);

/*
** semaphore functions
*/
int			unlock_sem_id(int semid);
int			lock_sem_id(int semid);

/*
** count functions
*/
int			count_player(t_lemipc *lemipc, player_type count_what);
int			count_id_map(t_lemipc *lemipc, int id);

/*
** free functions
*/
int			free_ipcs(t_lemipc *lemipc);
int			free_shared_resources(t_lemipc *lemipc);

/*
** map functions
*/
int			delete_player_from_map(t_lemipc *lemipc);

/*
** send messages
*/
void			int_to_mystring(char *buf, int nb, int begin);
int			mystring_to_int(char *src, int begin);
int			message_to_send(t_lemipc *lemipc, t_coord2d *enemy);

#endif /* !LEMIPC_H_ */
