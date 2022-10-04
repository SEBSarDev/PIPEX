NAME = pipex
CC = clang
FLAGS = -Wall -Werror -Wextra #-fsanitize=address
SRCS = src/main.c \
       src/execute.c \
       src/get_path.c \
       src/redir.c \
       src/utils.c \
       src/ft_split.c 
OBJS = $(SRCS:.c=.o)
$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -I./includes -o $(NAME)
all : $(NAME)
clean : 
	rm -rf $(OBJS)
fclean : clean
	rm -rf $(NAME)
re : fclean all
