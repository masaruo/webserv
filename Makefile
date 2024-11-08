# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 14:12:23 by mogawa            #+#    #+#              #
#    Updated: 2024/11/07 06:22:20 by mogawa           ###   ########.fr        #
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

ifdef WITH_GDB
CXXFLAGS	:=	$(filter-out -Werror, $(CXXFLAGS))
CXXFLAGS	+=	-ggdb -O0 -fsanitize=address,undefined -fno-limit-debug-info -fno-omit-frame-pointer
LDFLAGS		:=	-fsanitize=address,undefined
endif


all: $(TARGET)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

$(TARGET):	$(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

debug: fclean
	$(MAKE) all WITH_GDB=1

gdb: debug
	gdb ./$(TARGET)

clean:
	$(RM) -r $(OBJDIR)
	$(down)

fclean: clean
	$(RM) $(TARGET)

re: fclean
	$(MAKE) all

docker:
	docker container exec -it webserv bash

down:
	docker compose -f .devcontainer/docker-compose.yml down

val:
	valgrind ./$(TARGET)

-include $(DEP)

.PHONY: clean fclean re docker val up down

# $(info SRC=$(SRC))
