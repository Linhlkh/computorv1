NAME = computorv1

SRCS = main.cpp

OBJS = ${SRCS:.cpp=.o}

CXX = c++ -std=c++98 -g3

CXXFLAGS = -Wall -Werror -Wextra

${NAME}:	${OBJS}
		${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}

all:	${NAME}

bonus:	all

clean:
	@rm -rf ${OBJS}

fclean: clean
	@rm -rf ${NAME}

re: fclean all
