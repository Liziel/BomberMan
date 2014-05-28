NAME	= bomberman

CC	= g++
RM	= rm -f

SRC	=
INC	= -I ./includes

MAIN	= 	src/Main/main.cpp

SRC	= $(MAIN)

FLAGS	= -W -Wall -Wextra $(INC)				\
	-I lib/Gdl_lib/includes -L./lib/Gdl_lib/libs/ 	\
	-lgdl_gl -lGL -lGLEW -lSDL2 -ldl -lrt -lfbxsdk -lpthread
CFLAGS		+= $(FLAGS)
LDFLAGS		+= $(FLAGS)

OBJ		= $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(RM) src/Main/*.o

fclean: clean
	$(RM) $(NAME)

re: fclean all

.cpp.o:
	$(CC) -c -o $@ $< $(CFLAGS)
