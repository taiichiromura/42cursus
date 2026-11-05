NAME		=	phonebook
CXX         =   c++
CPPFLAGS	=	-Wall -Werror -Wextra -std=c++98

SRCS		=	PhoneBook.cpp	\
				Contact.cpp		\
				main.cpp		\

OBJS		=	$(SRCS:.cpp=.o)
DEPS        =   PhoneBook.hpp Contact.hpp

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CXX)  $(CPPFLAGS)  $(OBJS) -o $(NAME)

%.o: %.cpp $(DEPS)
				$(CXX) $(CPPFLAGS) -c $< -o $@
clean:
				@rm -f $(OBJS)

fclean:			clean
				@rm -f $(NAME)

re:				fclean all

.PHONY:         all clean fclean re
