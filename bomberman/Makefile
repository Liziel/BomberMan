NAME	= bomberman

CC	= g++
RM	= rm -f

SRC	=
INC	= -I ./includes
########################
#### MAIN
MAIN	= src/Main/main.cpp
########################
SRC	= $(MAIN)

FLAGS	= -W -Wall $(INC)				\
	-I lib/Gdl_lib/includes -L./lib/Gdl_lib/libs/ 	\
	-lgdl_gl -lGL -lGLEW -ldl -lrt -lfbxsdk -lpthread
CFLAGS		+= $(FLAGS)
LDFLAGS		+= $(FLAGS)

OBJ		= $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.cpp.o:
	$(CC) -c -o $@ $< $(CFLAGS)
