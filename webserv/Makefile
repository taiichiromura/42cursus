NAME        = webserv
CXX         = c++
CXXFLAGS    = -std=c++98 -Wall -Wextra -Werror -Iinclude -pedantic

VPATH = src:include

SRCS        = main.cpp \
			  ConfigParser.cpp \
			  ConfigServer.cpp \
			  Location.cpp \
			  Client.cpp \
			  Server.cpp \
              Server_Accept.cpp \
			  Server_Request.cpp \
			  Server_Dispatch.cpp \
			  Server_Cgi.cpp \
			  Response.cpp \
			  Response_Get.cpp \
			  Response_Utils.cpp \
			  Response_Post.cpp \
			  Response_Delete.cpp \
			  Cgi.cpp \
			  Utils.cpp \
			  ScopedFd.cpp

OBJS        = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
