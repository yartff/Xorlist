NAME		=	xorlist_tester

SRC		=	\
			main.c		\
			xorlist.c

OBJ		=	$(SRC:.c=.o)
CFLAGS		+=	-Wall -Wextra

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME)

all:		$(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
