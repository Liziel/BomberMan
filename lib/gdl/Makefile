NAME		=	../libgdl.so

SRC		=	src/BasicShader.cpp

OBJ		=	$(SRC:.cpp=.o)

RM		=	rm -f

CC		=	g++

CPPFLAGS	=	-fpic -shared -I./includes/

LDFLAGS		=	-L./libs/

all:			$(NAME)

$(NAME):		$(OBJ)
			$(CC) $(CPPFLAGS) $(LDFLAGS) $(OBJ) -o $(NAME)

clean:
			$(RM) $(OBJ)

fclean:			clean
			$(RM) $(NAME)

re:			fclean all