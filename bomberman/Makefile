NAME	= bomberman

CC	= g++
RM	= rm -f

SRC	=
INC	= -I ./includes

INC	= -I ./includes -I ./includes/Component/ -I ./includes/3dObject/
########################
#### MAIN
MAIN	= src/Main/main.cpp
#### EVENT
EVENT	= src/Event/Event.cpp
#### DATAPOOL & ENTITY
ENTITY	= src/Entity/entity.cpp src/Entity/factory.cpp
#### ENGINE
ENGINE	= src/Engine/game.cpp src/Engine/graphic.cpp src/Engine/manager.cpp
#### 3dObject
3DOBJECT= src/3dObject/cubeVertex.cpp  src/3dObject/AObject.cpp src/3dObject/planVertex.cpp src/3dObject/ziggsAnimated.cpp
#### COMPONENT
COMPO	= src/Component/Collider.cpp src/Component/Phisix.cpp src/Component/Health.cpp src/Component/Effects.cpp src/Component/Factory.cpp src/Component/abstract.cpp src/Component/plantBomb.cpp src/Component/Arena.cpp src/Component/Explode.cpp src/Component/Bonus.cpp src/Component/Runic.cpp src/Component/blocDisplay.cpp src/Component/joystick.cpp
########################
SRC	=  $(ENGINE) $(3DOBJECT) $(COMPO) $(ENTITY) $(EVENT) $(MAIN)

FLAGS	= -W -Wall -Wextra $(INC)				\
	-I lib/Gdl_lib/includes --std=c++11 -g3


CFLAGS		+= $(FLAGS)
LDFLAGS		= -L./lib/Gdl_lib/libs/ -lgdl_gl -lGL -lGLEW -lSDL2 -ldl -lrt -lfbxsdk -lpthread

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
