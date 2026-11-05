
NAME		=	program
CPPFLAGS	=	-Wall -Werror -Wextra -std=c++98

SRCS		=	tests.cpp	\
				Account.cpp	\

OBJS		=	$(SRCS:.cpp=.o)

$(NAME):		$(OBJS)
				$(CXX) $(CPPFLAGS) $(OBJS) -o $(NAME)

all:			$(NAME)

clean:
				rm -f $(OBJS)

fclean:			clean
				rm -f $(NAME)

re:				fclean all
