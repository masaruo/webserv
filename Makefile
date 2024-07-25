# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 14:12:23 by mogawa            #+#    #+#              #
#    Updated: 2024/07/23 14:49:23 by mogawa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET		:=	webserv
CXX			:=	c++
CXXFLAGS	:=	-Wall -Wextra -Werror -std=c++98 -MMD -MP
LDFLAGS		:=	
GTEST_INC	:=	-I./googletest/googletest/include -I./googletest/googlemock/include
GTEST_LIB	:=	-L./googletest/lib
INC			:=	-I./include -I./utility/include
SRC			=	 \
				string.cpp \
				Fcntl.class.cpp \
				ASocket.class.cpp \
				ClientSocket.class.cpp \
				ListenSocket.class.cpp \
				SocketHolder.class.cpp \
				main.cpp
SRCDIR		:=	./src
OBJDIR		:=	obj
OBJ			:=	$(SRC:%.cpp=$(OBJDIR)/%.o)
DEP			:=	$(SRC:%.cpp=$(OBJDIR)/%.d)

ifdef WITH_GTEST
CXXFLAGS	:=	-Wall -Wextra -std=c++17 $(GTEST_INC) -g3 -O0 -fsanitize=address,undefined
LDFLAGS		:=	$(GTEST_LIB) -lpthread -lgtest -lgtest_main -lgmock  -fsanitize=address,undefined
SRC			:=	$(filter-out main.cpp, $(SRC))
SRC			+=	$(wildcard ./test/*.cpp)
endif

ifdef WITH_LEAK
CXXFLAGS	:=	$(filter-out -Werror, $(CXXFLAGS))
CXXFLAGS	+=	-g3 -O0
endif

ifdef WITH_ASAN
CXXFLAGS	:=	$(filter-out -Werror, $(CXXFLAGS))
CXXFLAGS	+=	-g3 -O0 -fsanitize=address,undefined -Wshadow -Wconversion -Wno-sign-conversion -pedantic-errors -DDEBUG
LDFLAGS		:=	-fsanitize=address,undefined
endif

all: $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

$(TARGET):	$(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

gtest: fclean
	$(MAKE) all WITH_GTEST=1
	./$(TARGET)

leak: fclean
	$(MAKE) all WITH_LEAK=1
	leaks -q --atExit -- ./$(TARGET)

debug: fclean
	$(MAKE) all WITH_ASAN=1

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(TARGET)

re: fclean
	$(MAKE) all

dev: 
	./$(TARGET) 9 2 21 15 20 3 7 1 6 11 17 4 19 16 10 13 18 5 12 22 8 14

shuf:
	$(MAKE) all
	./$(TARGET) `gshuf -i 1-100000 -n 3000 | tr "\n" " "`

jot:
	$(MAKE) all
	./$(TARGET) `jot -r 3000 1 100000 | tr '\n' ' '`

-include $(DEP)

.PHONY: clean fclean re
