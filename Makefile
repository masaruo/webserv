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
CXXFLAGS	:=	-Wall -Wextra -Werror -Wconversion -std=c++98 -MMD -MP
LDFLAGS		:=	
INC			:=	-I./include \
				-I./include/config \
				-I./include/http/exception \
				-I./include/http/parts \
				-I./include/http/request \
				-I./include/http/response \
				-I./include/http/utility \
				-I./include/socket \
				-I./include/utility \
				-I./utility/include
SRC			:=	$(wildcard src/*.cpp) \
				$(wildcard src/*/*.cpp) \
				$(wildcard src/*/*/*.cpp)
SRCDIR		:=	$(sort $(dir $(SRC)))
VPATH		:=	$(SRCDIR)
OBJDIR		:=	obj
OBJ			:=	$(addprefix $(OBJDIR)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
DEP			:=	$(OBJ:.o=.d)

ifdef WITH_ASAN
CXXFLAGS	:=	$(filter-out -Werror, $(CXXFLAGS))
CXXFLAGS	+=	-ggdb -O0 -fsanitize=address,undefined,leak
LDFLAGS		:=	-fsanitize=address,undefined,leak
endif

$(info OBJ=$(OBJ))

all: $(TARGET)

$(OBJDIR)/%.o: %.cpp
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
