# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 14:12:23 by mogawa            #+#    #+#              #
#    Updated: 2024/07/26 16:39:33 by mogawa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET		:=	webserv
CXX			:=	c++
CXXFLAGS	:=	-Wall -Wextra -Werror -std=c++98 -MMD -MP
LDFLAGS		:=	
INC			:=	-I./include -I./utility/include
SRC			=	 \
				string.cpp \
				Fcntl.class.cpp \
				ASocket.class.cpp \
				ClientSocket.class.cpp \
				ListenSocket.class.cpp \
				SocketHolder.class.cpp \
				epoller.class.cpp \
				main.cpp
SRCDIR		:=	./src
OBJDIR		:=	obj
OBJ			:=	$(SRC:%.cpp=$(OBJDIR)/%.o)
DEP			:=	$(SRC:%.cpp=$(OBJDIR)/%.d)

#todo add vpath for multiple src & include for better maintainance
# vpath %.cpp $(src) $(SRC)/request $(SRC)/response $(SRC)/socket $(SRC)/utility
# vpath %.hpp ./include ./utility/include ./include/request ./include/response ./include/socket ./include/utility

ifdef WITH_ASAN
CXXFLAGS	:=	$(filter-out -Werror, $(CXXFLAGS))
CXXFLAGS	+=	-ggdb3 -Ogdb -fsanitize=address,undefined,leak -Wshadow -Wconversion -Wno-sign-conversion -pedantic-errors -DDEBUG
LDFLAGS		:=	-fsanitize=address,undefined,leak
endif

all: $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

$(TARGET):	$(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

debug: fclean
	$(MAKE) all WITH_ASAN=1

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(TARGET)

re: fclean
	$(MAKE) all

-include $(DEP)

.PHONY: clean fclean re
