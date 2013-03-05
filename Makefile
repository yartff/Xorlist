NAME		=	xorlist_tester
RM		=	@rm -rfv

SRC		=	\
			main.c		\
			xorlist.c

OBJ		=	$(SRC:.c=.o)
CFLAGS		+=	-Wall -Wextra
##CFLAGS		+=	-g3

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME)

all:		$(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
