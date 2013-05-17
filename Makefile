## Makefile for my_ftp in /home/lamais_g//Projects/SystemUnix/my_ftp
## 
## Made by gauthier lamaison
## Login   <lamais_g@epitech.net>
## 
## Started on  Wed Mar 30 19:41:43 2011 gauthier lamaison
## Last update Sun May 22 19:48:42 2011 axel catusse
##

########################################################################################
## VARIABLES
########################################################################################

LEMIPC			=	lemipc

INC_DIR			=	includes/
SRC_DIR			=	sources/

OBJS			=	$(SRCS:.c=.o)
INCLUDE			=	-I$(INC_DIR)
CFLAGS			+=	-W -Wall `sdl-config --cflags`
CFLAGS			+=	$(INCLUDE)
LDFLAGS			=	`sdl-config --libs` -lSDL_image -lSDL_gfx
CC			=	gcc
RM			=	rm -f
CLEAN			=	$(RM) $(SRC_DIR)*.c~		\
				$(RM) $(INC_DIR)*.h~		\

SRCS			=	$(SRC_DIR)main.c				\
				$(SRC_DIR)init_shared_mem.c			\
				$(SRC_DIR)dump_memory.c				\
				$(SRC_DIR)check_option.c			\
				$(SRC_DIR)count_func.c				\
				$(SRC_DIR)lock_func.c				\
				$(SRC_DIR)set_player_position.c			\
				$(SRC_DIR)start_graphic.c			\
				$(SRC_DIR)free_ipcs.c				\
				$(SRC_DIR)fork_to_start_graphic.c		\
				$(SRC_DIR)launch_lemipc.c			\
				$(SRC_DIR)delete_player_from_map.c		\
				$(SRC_DIR)player_random_move.c			\
				$(SRC_DIR)message_from_ally.c			\
				$(SRC_DIR)enemy_in_player_range.c		\
				$(SRC_DIR)player_is_dead.c			\
				$(SRC_DIR)move_player_to_enemy.c		\
				$(SRC_DIR)free_shared_memory.c			\
				$(SRC_DIR)display_map.c				\
				$(SRC_DIR)handle_event.c			\
				$(SRC_DIR)x_IMG_Load.c				\
				$(SRC_DIR)player_move.c				\
				$(SRC_DIR)end_game.c				\
				$(SRC_DIR)message_to_send.c			\
				$(SRC_DIR)raise_error.c				\


########################################################################################
## RULES
########################################################################################
all			:
			@make --no-print-directory $(LEMIPC)

$(LEMIPC)		:	$(OBJS)
			$(CC) -o $(LEMIPC) $(OBJS) $(LIBMY_LIST_WRAPPER) $(LDFLAGS)

clean			:
			$(RM) $(OBJS)

fclean			:	clean
			$(RM) $(LEMIPC)
			$(CLEAN)

re			:	fclean all

.PHONY			:	all clean fclean re
