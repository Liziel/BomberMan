NAME	= bomberman

CC	= g++
RM	= rm -f

SRC	=
INC	= -I ./includes -I ./includes/Component/
########################
#### MAIN
MAIN	= src/Main/main.cpp
#### EVENT
EVENT	= src/Event/Event.cpp
#### DATAPOOL & ENTITY
ENTITY	= src/DataPool/entity.cpp src/DataPool/datapool.cpp
#### COMPONENT
COMPO	= src/Component/Collider.cpp src/Component/Phisix.cpp src/Component/Health.cpp src/Component/Effects.cpp src/Component/Factory.cpp
########################
SRC	= $(COMPO) $(EVENT) $(MAIN)

FLAGS	= -W -Wall -std=c++11 $(INC) -g3			
#	-I lib/Gdl_lib/includes -L./lib/Gdl_lib/libs/ 	\
#	-lgdl_gl -lGL -lGLEW -lSDL2 -ldl -lrt -lfbxsdk -lpthread
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
