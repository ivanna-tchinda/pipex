NAME= pipex

SRC=	  main.c\
			utils.c\
			utils2.c\
			pipex_functs.c\
			processes.c\

CC= cc

OBJ_DIR= obj

CFLAGS= -Wall -Werror -Wextra

OBJ=	$(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))

RM=	rm -rf

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)

clean:		
		$(RM) $(OBJ)
		$(RM) $(OBJ_DIR)

fclean:		clean
			$(RM) $(NAME)

re:		fclean $(NAME)

.PHONY:	all clean fclean re