CC	=	g++

SFMLINK =	-lsfml-graphics -lsfml-window -lsfml-system -lGL -lGLU

CFLAGS	=	-W -Wextra

NAME	=	sfml_test

SRCS	=	main.cpp \
		Cube.cpp \
		Model.cpp \

OBJS	=	$(SRCS:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(SFMLINK) $(CFLAGS)

clean:
		rm -rf *.o

fclean:		clean
		rm -rf $(NAME)

re:		fclean all

ac:		re clean
