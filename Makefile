# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 14:12:23 by mogawa            #+#    #+#              #
#    Updated: 2024/10/15 17:46:11 by mogawa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET		:=	webserv
CXX			:=	clang++
CXXFLAGS	:=	-Wall -Wextra -Werror -std=c++98 -MMD -MP 
LDFLAGS		:=	
INCDIRS		:=	$(shell find include -type d)
INC			:=	$(addprefix -I, $(INCDIRS))

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
CXXFLAGS	+=	-ggdb -O0 -fsanitize=address,undefined,leak -fno-limit-debug-info
LDFLAGS		:=	-fsanitize=address,undefined,leak
endif


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

# $(info OBJ=$(OBJ))
