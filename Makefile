NAME	=	id_paint

SRC	=	$(wildcard *.cpp)

CC	=	g++

CFLAGS	+=	-Wall -Werror -W

LDFLAGS =	-lSDL -lSDL_ttf

OBJ	=	$(SRC:.cpp=.o)

%.o	:	%.cpp
	$(CC) $(CFLAGS) -c -o $*.o $<

$(NAME)	:	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean	:
	rm -f $(OBJ)

distclean	:	clean
	rm -rf $(NAME)

rebuild	:	distclean all

all	:	$(NAME)

debug		:	CFLAGS += -g3
debug		:	rebuild
